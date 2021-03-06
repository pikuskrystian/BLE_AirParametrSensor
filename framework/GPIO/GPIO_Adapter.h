/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef __GPIO_IRQ_ADAPTER_H__
#define __GPIO_IRQ_ADAPTER_H__

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"
#include "fsl_device_registers.h"


/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#ifndef gGpioMaxIsrEntries_c
#define gGpioMaxIsrEntries_c   (5)
#endif

#define gGpioDefaultNvicPrio_c (0x80)

#define gGpioIsrPrioHigh_c     (0)
#define gGpioIsrPrioNormal_c   (7)
#define gGpioIsrPrioLow_c      (15)

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
typedef void (*pfGpioIsrCb_t)(void);

typedef struct gpioIsr_tag{
    pfGpioIsrCb_t callback;
    uint32_t      pinMask;
    IRQn_Type     irqId;
    uint8_t       port;
    uint8_t       prio;
}gpioIsr_t;

typedef enum gpioStatus_tag{
    gpio_success,
    gpio_outOfMemory,
    gpio_notFound,
    gpio_error
}gpioStatus_t;

typedef enum gpioPort_tag
{
  gpioPort_A_c = 0,
  gpioPort_B_c = 1,
  gpioPort_C_c = 2,
  gpioPort_D_c = 3,
  gpioPort_E_c = 4,
  gpioPort_Invalid_c = 5
}gpioPort_t;

typedef enum portPull_tag
{
#if (FSL_FEATURE_SOC_INTMUX_COUNT <= 0) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)
	pinPull_Disabled_c  = 0U, /* High-Z ( no pull )*/
    pinPull_Down_c      = 1U, /* Pull down */
    pinPull_Up_c        = 2U, /* Pull up */
#else
    pinPull_Down_c      = 0U, /*!< Internal pull-down resistor is enabled. @internal gui name="Down"*/
    pinPull_Up_c        = 1U, /*!< Internal pull-up resistor is enabled. @internal gui name="Up"*/
    pinPull_Disabled_c  = 2U,
#endif
    pinPull_Invalid_c   = 3U,
} pinPullSelect_t;

typedef enum portInterrupt_tag
{
    pinInt_Disabled_c    = 0x0U,  /*!< Interrupt/DMA request is disabled.*/
    pinDma_RisingEdge_c  = 0x1U,  /*!< DMA request on rising edge.*/
    pinDma_FallingEdge_c = 0x2U,  /*!< DMA request on falling edge.*/
    pinDma_EitherEdge_c  = 0x3U,  /*!< DMA request on either edge.*/
    pinInt_LogicZero_c   = 0x8U,  /*!< Interrupt when logic zero. */
    pinInt_RisingEdge_c  = 0x9U,  /*!< Interrupt on rising edge. */
    pinInt_FallingEdge_c = 0xAU,  /*!< Interrupt on falling edge. */
    pinInt_EitherEdge_c  = 0xBU,  /*!< Interrupt on either edge. */
    pinInt_LogicOne_c    = 0xCU,  /*!< Interrupt when logic one. */
    pinInt_Invalid_c     = 0xDU,  /*!< Invalid enum value. */
} pinInterrupt_t;

/*! @brief Pin mux selection */
typedef enum
{
#if (FSL_FEATURE_SOC_INTMUX_COUNT <= 0) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)
    pinMux_Gpio_c = 0U,           /*!< corresponding pin is configured as GPIO. */
    pinMux_Alt1_c = 1U,           /*!< chip-specific */
#else
    pinMux_PinDisabledOrAnalog_c = 0U, /*!< corresponding pin is disabled, but is used as an analog pin. */
    pinMux_Gpio_c = 1U,           /*!< corresponding pin is configured as GPIO. */
    pinMux_Alt7_c = 7U,             /*!< chip-specific */
#endif
    pinMux_Alt2_c = 2U,             /*!< chip-specific */
    pinMux_Alt3_c = 3U,             /*!< chip-specific */
    pinMux_Alt4_c = 4U,             /*!< chip-specific */
    pinMux_Alt5_c = 5U,             /*!< chip-specific */
    pinMux_Alt6_c = 6U,             /*!< chip-specific */
} pinMux_t;

typedef enum portSlewRate_tag {
    pinSlewRate_Fast_c = 0U,  /*!< Fast slew rate is configured. @internal gui name="Fast"*/
    pinSlewRate_Slow_c = 1U,  /*!< Slow slew rate is configured. @internal gui name="Slow" */
    pinSlewRate_Invalid_c = 2U
} pinSlewRate_t;

/*! @brief Configures the drive strength.*/
typedef enum portDriveStrength_tag {
    pinDriveStrength_Low_c  = 0U, /*!< Low drive strength is configured. @internal gui name="Low"*/
    pinDriveStrength_High_c = 1U, /*!< High drive strength is configured. @internal gui name="High"*/
#if (FSL_FEATURE_SOC_INTMUX_COUNT <= 0) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)
  /* Extra and Full are only valid for QN9080 Port A, pins 6,11,19,26 and 27 */
    pinDriveStrength_Extra_c= 2U, /*!< Extra strength is configured. */
    pinDriveStrength_Full_c = 3U, /*!< High + Extra strength is configured. */
#endif
    pinDriveStrength_Invalid_c,   /*!< Invalid */
} pinDriveStrength_t;

typedef struct gpioInputPinConfig_tag
{
gpioPort_t   gpioPort;
uint8_t      gpioPin;
pinPullSelect_t pullSelect;
pinInterrupt_t interruptSelect;
}gpioInputPinConfig_t;

typedef struct gpioOutputPinConfig_tag
{
gpioPort_t   gpioPort;
uint8_t      gpioPin;
bool_t outputLogic;
pinSlewRate_t slewRate;
pinDriveStrength_t driveStrength;
}gpioOutputPinConfig_t;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
gpioStatus_t GpioInstallIsr( pfGpioIsrCb_t cb, uint8_t priority, uint8_t nvicPriority, const gpioInputPinConfig_t* pInputConfig );
gpioStatus_t GpioUninstallIsr( const gpioInputPinConfig_t* pInputConfig );
bool_t GpioInputPinInit(const gpioInputPinConfig_t* pInputConfig, uint32_t noOfElements );
bool_t GpioOutputPinInit(const gpioOutputPinConfig_t* pOutputConfig, uint32_t noOfElements );
uint32_t GpioReadOutputPin(const gpioOutputPinConfig_t* pOutputConfig);
uint32_t GpioReadPinInput(const gpioInputPinConfig_t* pInputConfig);
uint32_t GpioIsPinIntPending(const gpioInputPinConfig_t* pInputConfig);
void GpioClearPinIntFlag(const gpioInputPinConfig_t* pInputConfig);
void GpioSetPinOutput(const gpioOutputPinConfig_t* pOutputConfig);
void GpioClearPinOutput(const gpioOutputPinConfig_t* pOutputConfig);
void GpioTogglePinOutput(const gpioOutputPinConfig_t* pOutputConfig);
void GpioSetPinMux(gpioPort_t gpioPort, uint8_t gpioPin, pinMux_t pinMux);
void GpioSetPinMux_ISF_Preserved(gpioPort_t gpioPort, uint8_t gpioPin, pinMux_t pinMux);
void GpioSetPinPullMode(gpioPort_t gpioPort, uint8_t gpioPin, pinPullSelect_t pullSelect);
void GpioSetPassiveFilter(gpioPort_t gpioPort, uint8_t gpioPin, bool_t enable);
void GpioSetOpenDrain(gpioPort_t gpioPort, uint8_t gpioPin, bool_t enable);
void GpioSetSlewRate(gpioPort_t gpioPort, uint8_t gpioPin, pinSlewRate_t slewRate);
void GpioSetPinInterrupt(gpioPort_t gpioPort, uint8_t gpioPin, pinInterrupt_t mode);
pinInterrupt_t GpioGetPinInterrupt(gpioPort_t gpioPort, uint8_t gpioPin);
uint32_t GpioGetPinPCR(gpioPort_t gpioPort, uint8_t gpioPin);
void GpioSetPinPCR(gpioPort_t gpioPort, uint8_t gpioPin, uint32_t pcr);
void GpioSetPinPCR_ISF_Preserved(gpioPort_t gpioPort, uint8_t gpioPin, uint32_t pcr);

#if (FSL_FEATURE_SOC_INTMUX_COUNT <= 0) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)
void SetGpioWakeupLevel(GPIO_Type *base, uint32_t pin, uint8_t level);
#endif
#endif /* __GPIO_IRQ_ADAPTER_H__ */