/*! *********************************************************************************
 * \addtogroup Private Profile Server
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * \file
 *
 * This file is the source file for the QPP Server application
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/

/* Framework / Drivers */
#include "stdio.h"
#include "RNG_Interface.h"
#include "Keyboard.h"
#include "LED.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "SerialManager.h"
#include "MemManager.h"
#include "Panic.h"

/* BLE Host Stack */
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "battery_interface.h"
#include "device_info_interface.h"
#include "private_profile_interface.h"

/* Connection Manager */
#include "ble_conn_manager.h"

#include "board.h"
#include "ApplMain.h"
#include "private_profile_server.h"
#include "bmp280.h"
/************************************************************************************
 *************************************************************************************
 * Private macros
 *************************************************************************************
 ************************************************************************************/
#define mAttNotifHeaderSize_c                        (3)          /* ATT op code + ATT handle  */
#define mBatteryLevelReportInterval_c                (10)         /* battery level report interval in seconds  */
#define mQppsTxInterval_c                            (100)        /* Qpps send data interval in miliseconds  */
#define mQppsMaxTestDataLength_c                     (244)        /* the length of data that Qpps send every time*/

#define I2C_MASTER_CLOCK_FREQUENCY (16000000)
#define I2C_BMP ((I2C_Type*)I2C0_BASE)
/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/
typedef enum
{
#if gAppUseBonding_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
	fastWhiteListAdvState_c,
#endif
#endif
	fastAdvState_c,
	slowAdvState_c
}advType_t;

typedef struct advState_tag{
	bool_t      advOn;
	advType_t   advType;
}advState_t;

typedef struct appPeerInfo_tag
{
	uint8_t deviceId;
	uint8_t ntf_cfg;
	uint64_t bytsSentPerInterval;
	uint64_t bytsReceivedPerInterval;
}appPeerInfo_t;

typedef struct appTxInfo_tag
{
	uint32_t TakenSeconds;
	uint32_t RxSpeed[gAppMaxConnections_c];
	uint32_t TxSpeed[gAppMaxConnections_c];
}txInfo_t;

typedef struct
{
	float temperature;
	float humidity;
	float pressure;
}sensorData_t;
/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/
uint8_t gAppSerMgrIf;
/* Adv State */
static advState_t  mAdvState;
static bool_t      mRestartAdv;
static uint32_t    mAdvTimeout;
/* Service Data*/
static bool_t           basValidClientList[gAppMaxConnections_c] = { FALSE };
static basConfig_t      basServiceConfig = {service_battery, 0, basValidClientList, gAppMaxConnections_c};
static disConfig_t disServiceConfig = {service_device_info};
static qppsConfig_t qppServiceConfig = {service_qpps};

static uint16_t cpHandles[1] = {value_qpps_rx};

/* Application specific data*/
static tmrTimerID_t mAdvTimerId;
static tmrTimerID_t mBatteryMeasurementTimerId;
static tmrTimerID_t mQppsTxTimerId;

static appPeerInfo_t mPeerInformation[gAppMaxConnections_c];
static uint8_t printBuffer[100];

static uint8_t mQppsTestDataLength = (gAttDefaultMtu_c - mAttNotifHeaderSize_c);


BMP280_HandleTypedef bmp280;
sensorData_t sensorData;
/************************************************************************************
 *************************************************************************************
 * Private functions prototypes
 *************************************************************************************
 ************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent);
static void BleApp_Config(void);

/* Timer Callbacks */
static void AdvertisingTimerCallback (void *);
static void BatteryMeasurementTimerCallback (void *);
static void QppsTxTimerCallback(void* pParam);
static void QppsTxCallback(void * pParam);
static void BleApp_Advertise(void);

static void BleApp_ReceivedDataHandler
(
		deviceId_t  deviceId,
		uint8_t*    aValue,
		uint16_t    valueLength
);

/************************************************************************************
 *************************************************************************************
 * Public functions
 *************************************************************************************
 ************************************************************************************/

/*! *********************************************************************************
 * \brief    Initializes application specific functionality before the BLE stack init.
 *
 ********************************************************************************** */
void BleApp_Init(void)
{
	/* Initialize application support for drivers */
	BOARD_InitAdc();

	/* UI */
#if (defined(KW37A4_SERIES) || defined(KW37Z4_SERIES) || defined(KW38A4_SERIES) || defined(KW38Z4_SERIES) || defined(KW39A4_SERIES))
	Serial_InitManager();
#else
	SerialManager_Init();
#endif

	/* Register Serial Manager interface */
	Serial_InitInterface(&gAppSerMgrIf, APP_SERIAL_INTERFACE_TYPE, APP_SERIAL_INTERFACE_INSTANCE);
	Serial_SetBaudRate(gAppSerMgrIf, gUARTBaudRate115200_c);

	/* I2C*/
	i2c_master_config_t masterConfig; I2C_MasterGetDefaultConfig(&masterConfig);
	/* Change the default baudrate configuration */
	masterConfig.baudRate_Bps = 400000U;
	/* Initialize the I2C master peripheral */
	I2C_MasterInit(I2C_BMP, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);
	/* Initialize the BMP sensor */
	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = I2C_BMP;
	while (!bmp280_init(&bmp280, &bmp280.params)) {
		Serial_Print(gAppSerMgrIf, "BMP280 initialization failed\r\n", gNoBlock_d);
	}

}

/*! *********************************************************************************
 * \brief    Starts the BLE application.
 *
 ********************************************************************************** */
void BleApp_Start(void)
{
#if gAppUseBonding_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
	if (gcBondedDevices > 0)
	{
		mAdvState.advType = fastWhiteListAdvState_c;
	}
	else
#endif
	{
#endif
		mAdvState.advType = fastAdvState_c;
#if gAppUseBonding_d
	}
#endif

	BleApp_Advertise();
}

/*! *********************************************************************************
 * \brief        Handles keyboard events.
 *
 * \param[in]    events    Key event structure.
 ********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{
	uint8_t i;

	switch (events)
	{
	case gKBD_EventPressPB1_c:
	{
		for (i = 0; i < gAppMaxConnections_c; i++)
		{
			if (mPeerInformation[i].deviceId == gInvalidDeviceId_c)
				break;
		}
		if(i < gAppMaxConnections_c)
			BleApp_Start();
		break;
	}
	case gKBD_EventLongPB1_c:
	{
		for (i = 0; i < gAppMaxConnections_c; i++)
		{
			if (mPeerInformation[i].deviceId != gInvalidDeviceId_c)
				Gap_Disconnect(mPeerInformation[i].deviceId);
		}
		break;
	}
	case gKBD_EventLongPB2_c:
	{
		break;
	}
	default:
		break;
	}
}

/*! *********************************************************************************
 * \brief        Handles BLE generic callback.
 *
 * \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
 ********************************************************************************** */
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
	/* Call BLE Conn Manager */
	BleConnManager_GenericEvent(pGenericEvent);

	switch (pGenericEvent->eventType)
	{
	case gInitializationComplete_c:
	{
		BleApp_Config();
	}
	break;

	case gAdvertisingParametersSetupComplete_c:
	{
		(void)Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);
	}
	break;

	case gAdvertisingDataSetupComplete_c:
	{
		(void)App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
	}
	break;

	case gAdvertisingSetupFailed_c:
	{
		panic(0,0,0,0);
	}
	break;

	case gTxEntryAvailable_c:

		break;

	default:
		break;
	}
}

/************************************************************************************
 *************************************************************************************
 * Private functions
 *************************************************************************************
 ************************************************************************************/

/*! *********************************************************************************
 * \brief        Configures BLE Stack after initialization. Usually used for
 *               configuring advertising, scanning, white list, services, et al.
 *
 ********************************************************************************** */
static void BleApp_Config()
{
	/* Common GAP configuration */
	BleConnManager_GapCommonConfig();

	/* Register for callbacks*/
	GattServer_RegisterHandlesForWriteNotifications(NumberOfElements(cpHandles), cpHandles);
	App_RegisterGattServerCallback(BleApp_GattServerCallback);

	mAdvState.advOn = FALSE;
	for (uint8_t i = 0; i < gAppMaxConnections_c; i++)
	{
		mPeerInformation[i].deviceId= gInvalidDeviceId_c;
	}

	basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
	Bas_Start(&basServiceConfig);
	Dis_Start(&disServiceConfig);
	Qpp_Start (&qppServiceConfig);
	/* Allocate application timers */
	mAdvTimerId = TMR_AllocateTimer();
	mBatteryMeasurementTimerId = TMR_AllocateTimer();
	mQppsTxTimerId =  TMR_AllocateTimer();

	/* UI */
	//Serial_Print(gAppSerMgrIf, "\r\nPress ADVSW to connect to a QPP Client!\r\n", gNoBlock_d);
	BleApp_Start();
}

/*! *********************************************************************************
 * \brief        Configures GAP Advertise parameters. Advertise will start after
 *               the parameters are set.
 *
 ********************************************************************************** */
static void BleApp_Advertise(void)
{
	switch (mAdvState.advType)
	{
#if gAppUseBonding_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
	case fastWhiteListAdvState_c:
	{
		gAdvParams.minInterval = gFastConnMinAdvInterval_c;
		gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
		gAdvParams.filterPolicy = gProcessWhiteListOnly_c;
		mAdvTimeout = gFastConnWhiteListAdvTime_c;
	}
	break;
#endif
#endif
	case fastAdvState_c:
	{
		gAdvParams.minInterval = gFastConnMinAdvInterval_c;
		gAdvParams.maxInterval = gFastConnMaxAdvInterval_c;
		gAdvParams.filterPolicy = gProcessAll_c;
		mAdvTimeout = gFastConnAdvTime_c - gFastConnWhiteListAdvTime_c;
	}
	break;

	case slowAdvState_c:
	{
		gAdvParams.minInterval = gReducedPowerMinAdvInterval_c;
		gAdvParams.maxInterval = gReducedPowerMinAdvInterval_c;
		gAdvParams.filterPolicy = gProcessAll_c;
		mAdvTimeout = gReducedPowerAdvTime_c;
	}
	break;
	}

	/* Set advertising parameters*/
	Gap_SetAdvertisingParameters(&gAdvParams);
}

/*! *********************************************************************************
 * \brief        Handles BLE Advertising callback from host stack.
 *
 * \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
 ********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
	switch (pAdvertisingEvent->eventType)
	{
	case gAdvertisingStateChanged_c:
	{
		mAdvState.advOn = !mAdvState.advOn;

		if (!mAdvState.advOn && mRestartAdv)
		{
			BleApp_Advertise();
			break;
		}

		LED_StopFlashingAllLeds();
		Led1Flashing();

		if(!mAdvState.advOn)
		{
			Led2Flashing();
			Led3Flashing();
			Led4Flashing();
		}
		else
		{
			Serial_Print(gAppSerMgrIf, "\r\nAdvertising...\r\n", gNoBlock_d);
			TMR_StartLowPowerTimer(mAdvTimerId,gTmrLowPowerSecondTimer_c,
					TmrSeconds(mAdvTimeout), AdvertisingTimerCallback, NULL);
		}
	}
	break;

	case gAdvertisingCommandFailed_c:
	{
		panic(0,0,0,0);
	}
	break;

	default:
		break;
	}
}

/*! *********************************************************************************
 * \brief        Handles BLE Connection callback from host stack.
 *
 * \param[in]    peerDeviceId        Peer device ID.
 * \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
 ********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
	/* Connection Manager to handle Host Stack interactions */
	BleConnManager_GapPeripheralEvent(peerDeviceId, pConnectionEvent);

	switch (pConnectionEvent->eventType)
	{
	case gConnEvtConnected_c:
	{
		mPeerInformation[peerDeviceId].deviceId = peerDeviceId;
		Serial_Print(gAppSerMgrIf,"Connected with peerDeviceId = 0x",gNoBlock_d);
		Serial_PrintHex(gAppSerMgrIf, &peerDeviceId, 1, gNoBlock_d);
		Serial_Print(gAppSerMgrIf, "\r\n", gNoBlock_d);
		/* Advertising stops when connected */
		mAdvState.advOn = FALSE;

		/* Subscribe client*/
		Bas_Subscribe(&basServiceConfig, peerDeviceId);
		Qpp_Subscribe(peerDeviceId);
		/* UI */
		LED_StopFlashingAllLeds();
		Led1On();
		/* Stop Advertising Timer*/
		mAdvState.advOn = FALSE;
		TMR_StopTimer(mAdvTimerId);

		/* Start battery measurements */
		if(!TMR_IsTimerActive(mBatteryMeasurementTimerId))
		{
			TMR_StartLowPowerTimer(mBatteryMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
					TmrSeconds(mBatteryLevelReportInterval_c), BatteryMeasurementTimerCallback, NULL);
		}

		if(!TMR_IsTimerActive(mQppsTxTimerId))
		{
			TMR_StartLowPowerTimer(mQppsTxTimerId, gTmrLowPowerIntervalMillisTimer_c,
					mQppsTxInterval_c, QppsTxTimerCallback, NULL);
		}
	}
	break;

	case gConnEvtDisconnected_c:
	{
		/* Unsubscribe client */
		Bas_Unsubscribe(&basServiceConfig, peerDeviceId);
		/* qpps Unsubscribe client */
		Qpp_Unsubscribe();
		mPeerInformation[peerDeviceId].bytsReceivedPerInterval = 0;
		mPeerInformation[peerDeviceId].bytsSentPerInterval = 0;
		mPeerInformation[peerDeviceId].ntf_cfg = QPPS_VALUE_NTF_OFF;
		mPeerInformation[peerDeviceId].deviceId = gInvalidDeviceId_c;

		for (uint8_t i = 0; i < gAppMaxConnections_c; i++)
		{
			if(mPeerInformation[i].deviceId != gInvalidDeviceId_c)
				break;
			if(i==(gAppMaxConnections_c-1))
			{
				TMR_StopTimer(mBatteryMeasurementTimerId);
				TMR_StopTimer(mQppsTxTimerId);
			}
		}

		if (pConnectionEvent->eventData.disconnectedEvent.reason == gHciConnectionTimeout_c)
		{
			/* Link loss detected*/
			BleApp_Start();
		}
		else
		{
			/* Connection was terminated by peer or application */
			BleApp_Start();
		}
	}
	break;
	default:
		break;
	}
}

/*! *********************************************************************************
 * \brief        Handles GATT server callback from host stack.
 *
 * \param[in]    deviceId        Peer device ID.
 * \param[in]    pServerEvent    Pointer to gattServerEvent_t.
 ********************************************************************************** */
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
	uint16_t handle;
	uint8_t status;
	uint8_t notifMaxPayload = 0;
	switch (pServerEvent->eventType)
	{
	case gEvtMtuChanged_c:
		notifMaxPayload = pServerEvent->eventData.mtuChangedEvent.newMtu - mAttNotifHeaderSize_c;
		if( notifMaxPayload <= mQppsMaxTestDataLength_c )
		{
			mQppsTestDataLength = notifMaxPayload;
		}
		break;

	case gEvtAttributeWritten_c:
	{
		handle = pServerEvent->eventData.attributeWrittenEvent.handle;
		status = gAttErrCodeNoError_c;
		GattServer_SendAttributeWrittenStatus(deviceId, handle, status);
	}
	break;

	case gEvtAttributeWrittenWithoutResponse_c:
	{
		handle = pServerEvent->eventData.attributeWrittenEvent.handle;

		if (handle == value_qpps_rx)
		{
			BleApp_ReceivedDataHandler(deviceId, pServerEvent->eventData.attributeWrittenEvent.aValue, pServerEvent->eventData.attributeWrittenEvent.cValueLength);
		}
	}
	break;

	case gEvtCharacteristicCccdWritten_c:
	{
		handle = pServerEvent->eventData.charCccdWrittenEvent.handle;
		if (handle == cccd_qpps_tx)
		{
			mPeerInformation[deviceId].ntf_cfg = pServerEvent->eventData.charCccdWrittenEvent.newCccd;

		}
	}
	break;

	default:
		break;
	}
}

static void BleApp_ReceivedDataHandler (deviceId_t deviceId, uint8_t* aValue, uint16_t valueLength)
{
	for(int i=0;i<valueLength;i++)
		printBuffer[i]=aValue[i];
	printBuffer[valueLength]=0;

	Serial_Print(gAppSerMgrIf, (char*)printBuffer, gNoBlock_d);
}

/*! *********************************************************************************
 * \brief        Handles advertising timer callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void AdvertisingTimerCallback(void * pParam)
{
	/* Stop and restart advertising with new parameters */
	Gap_StopAdvertising();

	switch (mAdvState.advType)
	{
#if gAppUseBonding_d
#if defined(gBleEnableControllerPrivacy_d) && (gBleEnableControllerPrivacy_d > 0)
	case fastWhiteListAdvState_c:
	{
		mAdvState.advType = fastAdvState_c;
		mRestartAdv = TRUE;
	}
	break;
#endif
#endif
	case fastAdvState_c:
	{
		mAdvState.advType = slowAdvState_c;
		mRestartAdv = TRUE;
	}
	break;

	default:
	{
		mRestartAdv = FALSE;
	}
	break;
	}
}

/*! *********************************************************************************
 * \brief        Handles QPP tx timer callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */

static void QppsTxTimerCallback(void * pParam)
{
	bleResult_t result;
	uint8_t *tx_data =(uint8_t*) &sensorData;
	mQppsTestDataLength=sizeof(sensorData_t);
	bmp280_read_float(&bmp280, &sensorData.temperature, &sensorData.pressure, &sensorData.humidity);
	for (int i = 0; i < gAppMaxConnections_c; i++) {
		if ((mPeerInformation[i].deviceId != gInvalidDeviceId_c) && (mPeerInformation[i].ntf_cfg == QPPS_VALUE_NTF_ON)) {
			result = Qpp_SendData(mPeerInformation[i].deviceId, service_qpps, mQppsTestDataLength, tx_data);
			if(result != gBleSuccess_c){
				Serial_Print(gAppSerMgrIf, "Send ERROR!\r\n", gNoBlock_d);
			}
		}
	}
}

/*! *********************************************************************************
 * \brief        QPP tx callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void QppsTxCallback(void * pParam)
{
	static uint8_t tx_data[mQppsMaxTestDataLength_c];
	static uint8_t index = 0;
	bleResult_t result;

	sprintf((char*)tx_data, "sample: %d\r\n", index++);
	mQppsTestDataLength=strlen((char*)tx_data);

	for (int i = 0; i < gAppMaxConnections_c; i++) {
		if ((mPeerInformation[i].deviceId != gInvalidDeviceId_c) && (mPeerInformation[i].ntf_cfg == QPPS_VALUE_NTF_ON)) {
			result = Qpp_SendData(mPeerInformation[i].deviceId, service_qpps, mQppsTestDataLength, tx_data);
			if(result != gBleSuccess_c){
				Serial_Print(gAppSerMgrIf, "Send ERROR!\r\n", gNoBlock_d);
			}
		}
	}
}

/*! *********************************************************************************
 * \brief        Handles battery measurement timer callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void BatteryMeasurementTimerCallback(void * pParam)
{
	basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
	Bas_RecordBatteryMeasurement(&basServiceConfig);
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
