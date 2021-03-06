/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_flexcomm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to real IRQ handlers installed by drivers for each instance. */
static flexcomm_irq_handler_t s_flexcommIrqHandler[FSL_FEATURE_SOC_FLEXCOMM_COUNT];

/*! @brief Pointers to handles for each instance to provide context to interrupt routines */
static void *s_flexcommHandle[FSL_FEATURE_SOC_FLEXCOMM_COUNT];

/*! @brief Array to map FLEXCOMM instance number to IRQ number. */
IRQn_Type const kFlexcommIrqs[] = FLEXCOMM_IRQS;

/*! @brief Array to map FLEXCOMM instance number to base address. */
static const uint32_t s_flexcommBaseAddrs[FSL_FEATURE_SOC_FLEXCOMM_COUNT] = FLEXCOMM_BASE_ADDRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief IDs of clock for each FLEXCOMM module */
static const clock_ip_name_t s_flexcommClocks[] = FLEXCOMM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

/* check whether flexcomm supports peripheral type */
static bool FLEXCOMM_PeripheralIsPresent(FLEXCOMM_Type *base, FLEXCOMM_PERIPH_T periph)
{
    if (periph == FLEXCOMM_PERIPH_NONE)
    {
        return true;
    }
    else if ((periph >= FLEXCOMM_PERIPH_USART) && (periph <= FLEXCOMM_PERIPH_I2S_TX))
    {
        return (base->PSELID & (uint32_t)(1 << ((uint32_t)periph + 3))) > 0 ? true : false;
    }
    else if (periph == FLEXCOMM_PERIPH_I2S_RX)
    {
        return (base->PSELID & (1 << 7)) > 0 ? true : false;
    }
    else
    {
        return false;
    }
}

/* Get the index corresponding to the FLEXCOMM */
uint32_t FLEXCOMM_GetInstance(void *base)
{
    int i;

    for (i = 0; i < FSL_FEATURE_SOC_FLEXCOMM_COUNT; i++)
    {
        if ((uint32_t)base == s_flexcommBaseAddrs[i])
        {
            return i;
        }
    }

    assert(false);
    return 0;
}

/* Changes FLEXCOMM mode */
status_t FLEXCOMM_SetPeriph(FLEXCOMM_Type *base, FLEXCOMM_PERIPH_T periph, int lock)
{
    /* Check whether peripheral type is present */
    if (!FLEXCOMM_PeripheralIsPresent(base, periph))
    {
        return kStatus_OutOfRange;
    }

    /* Flexcomm is locked to different peripheral type than expected  */
    if ((base->PSELID & FLEXCOMM_PSELID_LOCK_MASK) && ((base->PSELID & FLEXCOMM_PSELID_PERSEL_MASK) != periph))
    {
        return kStatus_Fail;
    }

    /* Check if we are asked to lock */
    if (lock)
    {
        base->PSELID = (uint32_t)periph | FLEXCOMM_PSELID_LOCK_MASK;
    }
    else
    {
        base->PSELID = (uint32_t)periph;
    }

    return kStatus_Success;
}

status_t FLEXCOMM_Init(void *base, FLEXCOMM_PERIPH_T periph)
{
    int idx = FLEXCOMM_GetInstance(base);

    if (idx < 0)
    {
        return kStatus_InvalidArgument;
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the peripheral clock */
    CLOCK_EnableClock(s_flexcommClocks[idx]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Set the FLEXCOMM to given peripheral */
    return FLEXCOMM_SetPeriph((FLEXCOMM_Type *)base, periph, 0);
}

void FLEXCOMM_SetIRQHandler(void *base, flexcomm_irq_handler_t handler, void *handle)
{
    uint32_t instance;

    /* Look up instance number */
    instance = FLEXCOMM_GetInstance(base);

    /* Clear handler first to avoid execution of the handler with wrong handle */
    s_flexcommIrqHandler[instance] = NULL;
    s_flexcommHandle[instance] = handle;
    s_flexcommIrqHandler[instance] = handler;
}

/* IRQ handler functions overloading weak symbols in the startup */
#if defined(FLEXCOMM0)
void FLEXCOMM0_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[0]);
    s_flexcommIrqHandler[0]((void *)s_flexcommBaseAddrs[0], s_flexcommHandle[0]);
}
#endif

#if defined(FLEXCOMM1)
void FLEXCOMM1_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[1]);
    s_flexcommIrqHandler[1]((void *)s_flexcommBaseAddrs[1], s_flexcommHandle[1]);
}
#endif

#if defined(FLEXCOMM2)
void FLEXCOMM2_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[2]);
    s_flexcommIrqHandler[2]((void *)s_flexcommBaseAddrs[2], s_flexcommHandle[2]);
}
#endif

#if defined(FLEXCOMM3)
void FLEXCOMM3_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[3]);
    s_flexcommIrqHandler[3]((void *)s_flexcommBaseAddrs[3], s_flexcommHandle[3]);
}
#endif

#if defined(FLEXCOMM4)
void FLEXCOMM4_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[4]);
    s_flexcommIrqHandler[4]((void *)s_flexcommBaseAddrs[4], s_flexcommHandle[4]);
}

#endif

#if defined(FLEXCOMM5)
void FLEXCOMM5_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[5]);
    s_flexcommIrqHandler[5]((void *)s_flexcommBaseAddrs[5], s_flexcommHandle[5]);
}
#endif

#if defined(FLEXCOMM6)
void FLEXCOMM6_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[6]);
    s_flexcommIrqHandler[6]((void *)s_flexcommBaseAddrs[6], s_flexcommHandle[6]);
}
#endif

#if defined(FLEXCOMM7)
void FLEXCOMM7_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[7]);
    s_flexcommIrqHandler[7]((void *)s_flexcommBaseAddrs[7], s_flexcommHandle[7]);
}
#endif

#if defined(FLEXCOMM8)
void FLEXCOMM8_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[8]);
    s_flexcommIrqHandler[8]((void *)s_flexcommBaseAddrs[8], s_flexcommHandle[8]);
}
#endif

#if defined(FLEXCOMM9)
void FLEXCOMM9_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[9]);
    s_flexcommIrqHandler[9]((void *)s_flexcommBaseAddrs[9], s_flexcommHandle[9]);
}
#endif
