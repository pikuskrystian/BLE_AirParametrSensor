/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017, 2020 NXP
* All rights reserved.
*
* \file
*
* TMR export interface file for ARM CORTEX processor
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef TMR_ADAPTER_H
#define TMR_ADAPTER_H


/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
***********************************************************************************/
#include "EmbeddedTypes.h"
#include "fsl_device_registers.h"
#include "board.h"


/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/

#ifndef gStackTimerInstance_c
#define gStackTimerInstance_c  0
#endif

#ifndef gStackTimerChannel_c
#define gStackTimerChannel_c   0
#endif

#ifndef gLptmrInstance_c
#define gLptmrInstance_c       0
#endif

#ifndef gTmrRtcInstance_c
#define gTmrRtcInstance_c      0
#endif

#ifndef gTmrPitInstance_c
#define gTmrPitInstance_c      0
#endif

#ifndef gCFC_XTAL1_USE_CALIB_c
#define gCFC_XTAL1_USE_CALIB_c    0
#endif

#ifndef gCFG_MCU_HAS_FPU_c
#define gCFG_MCU_HAS_FPU_c    0
#endif

#define gStackTimer_IsrPrio_c (0x80)

#if FSL_FEATURE_SOC_CTIMER_COUNT || FSL_FEATURE_RTC_HAS_FRC
#define gStackTimerMaxCountValue_c  0xffffffff
#else
#define gStackTimerMaxCountValue_c  0xffff
#endif
/************************************************************************************
*************************************************************************************
* Public types
*************************************************************************************
************************************************************************************/
typedef struct _tmr_adapter_pwm_param_type
{
    uint32_t frequency;
    uint32_t initValue;
}tmr_adapter_pwm_param_t;


/*
 * \brief   Platofrm specific timer ticks type definition
 */
#if FSL_FEATURE_SOC_CTIMER_COUNT || FSL_FEATURE_RTC_HAS_FRC
    typedef uint32_t tmrTimerTicks_t;
#else
    typedef uint16_t tmrTimerTicks_t;
#endif
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
void StackTimer_Init(void (*cb)(void));
void StackTimer_Enable(void);
void StackTimer_Disable(void);
void StackTimer_ClearIntFlag(void);
uint32_t StackTimer_GetInputFrequency(void);
uint32_t StackTimer_GetCounterValue(void);
void StackTimer_SetOffsetTicks(uint32_t offset);

void PWM_Init(uint8_t instance);
void PWM_SetChnCountVal(uint8_t instance, uint8_t channel, tmrTimerTicks_t val);
tmrTimerTicks_t PWM_GetChnCountVal(uint8_t instance, uint8_t channel);
#if !defined(FSL_FEATURE_SOC_CTIMER_COUNT) || (FSL_FEATURE_SOC_CTIMER_COUNT == 0)
void PWM_StartEdgeAlignedLowTrue(uint8_t instance, tmr_adapter_pwm_param_t *param, uint8_t channel);
#endif
#endif /* TMR_ADAPTER_H */