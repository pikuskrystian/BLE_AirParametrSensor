/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* This is the header file for the Panic module.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef PANIC_H
#define PANIC_H

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"


/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

typedef uint32_t panicId_t;

typedef struct
{
    panicId_t id;
    uint32_t location;
    uint32_t extra1;
    uint32_t extra2;
    uint32_t linkRegister;
    uint32_t cpsr_contents;   /* may not be used initially */
    uint8_t stack_dump[4];    /* initially just contain the contents of the LR */
} panicData_t;


/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#ifndef gUsePanic_c
#define gUsePanic_c 0
#endif

#define ID_PANIC(grp,value) ((panicId_t)(((panicId_t)(grp) << 16)+((panicId_t)(value))))

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
void panic
(
    panicId_t id,
    uint32_t location,
    uint32_t extra1,
    uint32_t extra2
);

#endif /* PANIC_H */