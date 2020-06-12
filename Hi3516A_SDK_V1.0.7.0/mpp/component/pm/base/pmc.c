//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  pmc.c
// Author        :  xxx
// Version       :  1.0 
// Date          :  2014-06-19
// Description   :  Define all registers/tables for xxx
// Others        :  Generated automatically by nManager V4.0 
// History       :  xxx 2014-06-19 Create file
//******************************************************************************
#include <linux/io.h>
#include "pmc.h"
#include <linux/kernel.h>
#include <mach/io.h>/* for IO_ADDRESS */

/* The base address of the module PMC */
#define PMC_BASE_ADDR 0x20270000

/* Define the struct pointor of the module PMC */
S_PMC_REGS_TYPE *gopPMCAllReg = (S_PMC_REGS_TYPE *)IO_ADDRESS(PMC_BASE_ADDR);

#define RTL_Verify_RegWrite(addr, p)

//******************************************************************************
//  Function    : iSetPERI_PMC0core_pwm_period
//  Description : Set the value of the member PERI_PMC0.core_pwm_period
//  Input       : unsigned int ucore_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC0core_pwm_period(unsigned int ucore_pwm_period)
{
    U_PERI_PMC0 o_peri_pmc0;
    o_peri_pmc0.u32 = gopPMCAllReg->PERI_PMC0.u32;
    o_peri_pmc0.bits.core_pwm_period = ucore_pwm_period;
    gopPMCAllReg->PERI_PMC0.u32 = o_peri_pmc0.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC0.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC0core_pwm_duty
//  Description : Set the value of the member PERI_PMC0.core_pwm_duty
//  Input       : unsigned int ucore_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC0core_pwm_duty(unsigned int ucore_pwm_duty)
{
    U_PERI_PMC0 o_peri_pmc0;
    o_peri_pmc0.u32 = gopPMCAllReg->PERI_PMC0.u32;
    o_peri_pmc0.bits.core_pwm_duty = ucore_pwm_duty;
    gopPMCAllReg->PERI_PMC0.u32 = o_peri_pmc0.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC0.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC1cpu_pwm_period
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_period
//  Input       : unsigned int ucpu_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC1cpu_pwm_period(unsigned int ucpu_pwm_period)
{
    U_PERI_PMC1 o_peri_pmc1;
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC1.u32;
    o_peri_pmc1.bits.cpu_pwm_period = ucpu_pwm_period;
    gopPMCAllReg->PERI_PMC1.u32 = o_peri_pmc1.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC1.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC1cpu_pwm_duty
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_duty
//  Input       : unsigned int ucpu_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC1cpu_pwm_duty(unsigned int ucpu_pwm_duty)
{
    U_PERI_PMC1 o_peri_pmc1;
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC1.u32;
    o_peri_pmc1.bits.cpu_pwm_duty = ucpu_pwm_duty;
    gopPMCAllReg->PERI_PMC1.u32 = o_peri_pmc1.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC1.u32));

    return 1;
}

//******************************************************************************
//  Function    : iGetPERI_PMC1cpu_pwm_period
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_period
//  Input       : unsigned int ucpu_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iGetPERI_PMC1cpu_pwm_period(void)
{
    U_PERI_PMC1 o_peri_pmc1;
    unsigned int ucpu_pwm_period;
    
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC1.u32;
    ucpu_pwm_period = o_peri_pmc1.bits.cpu_pwm_period;
    return ucpu_pwm_period;
}

//******************************************************************************
//  Function    : iGetPERI_PMC1cpu_pwm_duty
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_duty
//  Input       : unsigned int ucpu_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iGetPERI_PMC1cpu_pwm_duty(void)
{
    U_PERI_PMC1 o_peri_pmc1;
    unsigned int ucpu_pwm_duty;
    
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC1.u32;
    ucpu_pwm_duty = o_peri_pmc1.bits.cpu_pwm_duty;
    
    return ucpu_pwm_duty;
}

//******************************************************************************
//  Function    : iSetPERI_PMC2ddr_pwm_period
//  Description : Set the value of the member PERI_PMC2.ddr_pwm_period
//  Input       : unsigned int uddr_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC2ddr_pwm_period(unsigned int uddr_pwm_period)
{
    U_PERI_PMC2 o_peri_pmc2;
    o_peri_pmc2.u32 = gopPMCAllReg->PERI_PMC2.u32;
    o_peri_pmc2.bits.ddr_pwm_period = uddr_pwm_period;
    gopPMCAllReg->PERI_PMC2.u32 = o_peri_pmc2.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC2.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC2ddr_pwm_duty
//  Description : Set the value of the member PERI_PMC2.ddr_pwm_duty
//  Input       : unsigned int uddr_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC2ddr_pwm_duty(unsigned int uddr_pwm_duty)
{
    U_PERI_PMC2 o_peri_pmc2;
    o_peri_pmc2.u32 = gopPMCAllReg->PERI_PMC2.u32;
    o_peri_pmc2.bits.ddr_pwm_duty = uddr_pwm_duty;
    gopPMCAllReg->PERI_PMC2.u32 = o_peri_pmc2.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC2.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC3mda_pwm_period
//  Description : Set the value of the member PERI_PMC3.mda_pwm_period
//  Input       : unsigned int umda_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC3mda_pwm_period(unsigned int umda_pwm_period)
{
    U_PERI_PMC3 o_peri_pmc3;
    o_peri_pmc3.u32 = gopPMCAllReg->PERI_PMC3.u32;
    o_peri_pmc3.bits.mda_pwm_period = umda_pwm_period;
    gopPMCAllReg->PERI_PMC3.u32 = o_peri_pmc3.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC3.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC3mda_pwm_duty
//  Description : Set the value of the member PERI_PMC3.mda_pwm_duty
//  Input       : unsigned int umda_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC3mda_pwm_duty(unsigned int umda_pwm_duty)
{
    U_PERI_PMC3 o_peri_pmc3;
    o_peri_pmc3.u32 = gopPMCAllReg->PERI_PMC3.u32;
    o_peri_pmc3.bits.mda_pwm_duty = umda_pwm_duty;
    gopPMCAllReg->PERI_PMC3.u32 = o_peri_pmc3.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC3.u32));

    return 1;
}

//******************************************************************************
//  Function    : iGetPERI_PMC1cpu_pwm_period
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_period
//  Input       : unsigned int ucpu_pwm_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iGetPERI_PMC3mda_pwm_period(void)
{
    U_PERI_PMC1 o_peri_pmc1;
    unsigned int ucpu_pwm_period;
    
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC3.u32;
    ucpu_pwm_period = o_peri_pmc1.bits.cpu_pwm_period;
    return ucpu_pwm_period;
}

//******************************************************************************
//  Function    : iGetPERI_PMC1cpu_pwm_duty
//  Description : Set the value of the member PERI_PMC1.cpu_pwm_duty
//  Input       : unsigned int ucpu_pwm_duty: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iGetPERI_PMC3mda_pwm_duty(void)
{
    U_PERI_PMC1 o_peri_pmc1;
    unsigned int ucpu_pwm_duty;
    
    o_peri_pmc1.u32 = gopPMCAllReg->PERI_PMC3.u32;
    ucpu_pwm_duty = o_peri_pmc1.bits.cpu_pwm_duty;
    
    return ucpu_pwm_duty;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4core_pwm_enable
//  Description : Set the value of the member PERI_PMC4.core_pwm_enable
//  Input       : unsigned int ucore_pwm_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4core_pwm_enable(unsigned int ucore_pwm_enable)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.core_pwm_enable = ucore_pwm_enable;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4core_pwm_inv
//  Description : Set the value of the member PERI_PMC4.core_pwm_inv
//  Input       : unsigned int ucore_pwm_inv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4core_pwm_inv(unsigned int ucore_pwm_inv)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.core_pwm_inv = ucore_pwm_inv;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4cpu_pwm_enable
//  Description : Set the value of the member PERI_PMC4.cpu_pwm_enable
//  Input       : unsigned int ucpu_pwm_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4cpu_pwm_enable(unsigned int ucpu_pwm_enable)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.cpu_pwm_enable = ucpu_pwm_enable;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

int iGetPERI_PMC4cpu_pwm_enable(unsigned int *ucpu_pwm_enable)
{
    *ucpu_pwm_enable = gopPMCAllReg->PERI_PMC4.bits.cpu_pwm_enable;

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4cpu_pwm_inv
//  Description : Set the value of the member PERI_PMC4.cpu_pwm_inv
//  Input       : unsigned int ucpu_pwm_inv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4cpu_pwm_inv(unsigned int ucpu_pwm_inv)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.cpu_pwm_inv = ucpu_pwm_inv;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4ddr_pwm_enable
//  Description : Set the value of the member PERI_PMC4.ddr_pwm_enable
//  Input       : unsigned int uddr_pwm_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4ddr_pwm_enable(unsigned int uddr_pwm_enable)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.ddr_pwm_enable = uddr_pwm_enable;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4ddr_pwm_inv
//  Description : Set the value of the member PERI_PMC4.ddr_pwm_inv
//  Input       : unsigned int uddr_pwm_inv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4ddr_pwm_inv(unsigned int uddr_pwm_inv)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.ddr_pwm_inv = uddr_pwm_inv;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4mda_pwm_enable
//  Description : Set the value of the member PERI_PMC4.mda_pwm_enable
//  Input       : unsigned int umda_pwm_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4mda_pwm_enable(unsigned int umda_pwm_enable)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.mda_pwm_enable = umda_pwm_enable;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

int iGetPERI_PMC4mda_pwm_enable(unsigned int *umda_pwm_enable)
{
    *umda_pwm_enable = gopPMCAllReg->PERI_PMC4.bits.mda_pwm_enable;

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4mda_pwm_inv
//  Description : Set the value of the member PERI_PMC4.mda_pwm_inv
//  Input       : unsigned int umda_pwm_inv: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4mda_pwm_inv(unsigned int umda_pwm_inv)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.mda_pwm_inv = umda_pwm_inv;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4pwm0_reuse_cfg
//  Description : Set the value of the member PERI_PMC4.pwm0_reuse_cfg
//  Input       : unsigned int upwm0_reuse_cfg: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4pwm0_reuse_cfg(unsigned int upwm0_reuse_cfg)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.pwm0_reuse_cfg = upwm0_reuse_cfg;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4pwm1_reuse_cfg
//  Description : Set the value of the member PERI_PMC4.pwm1_reuse_cfg
//  Input       : unsigned int upwm1_reuse_cfg: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4pwm1_reuse_cfg(unsigned int upwm1_reuse_cfg)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.pwm1_reuse_cfg = upwm1_reuse_cfg;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4pwm2_reuse_cfg
//  Description : Set the value of the member PERI_PMC4.pwm2_reuse_cfg
//  Input       : unsigned int upwm2_reuse_cfg: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4pwm2_reuse_cfg(unsigned int upwm2_reuse_cfg)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.pwm2_reuse_cfg = upwm2_reuse_cfg;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC4pwm3_reuse_cfg
//  Description : Set the value of the member PERI_PMC4.pwm3_reuse_cfg
//  Input       : unsigned int upwm3_reuse_cfg: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC4pwm3_reuse_cfg(unsigned int upwm3_reuse_cfg)
{
    U_PERI_PMC4 o_peri_pmc4;
    o_peri_pmc4.u32 = gopPMCAllReg->PERI_PMC4.u32;
    o_peri_pmc4.bits.pwm3_reuse_cfg = upwm3_reuse_cfg;
    gopPMCAllReg->PERI_PMC4.u32 = o_peri_pmc4.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC4.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC5core_hpm_fsm_en
//  Description : Set the value of the member PERI_PMC5.core_hpm_fsm_en
//  Input       : unsigned int ucore_hpm_fsm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC5core_hpm_fsm_en(unsigned int ucore_hpm_fsm_en)
{
    U_PERI_PMC5 o_peri_pmc5;
    o_peri_pmc5.u32 = gopPMCAllReg->PERI_PMC5.u32;
    o_peri_pmc5.bits.core_hpm_fsm_en = ucore_hpm_fsm_en;
    gopPMCAllReg->PERI_PMC5.u32 = o_peri_pmc5.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC5.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC5core_avs_hpm_fsm_calc_mode
//  Description : Set the value of the member PERI_PMC5.core_avs_hpm_fsm_calc_mode
//  Input       : unsigned int ucore_avs_hpm_fsm_calc_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC5core_avs_hpm_fsm_calc_mode(unsigned int ucore_avs_hpm_fsm_calc_mode)
{
    U_PERI_PMC5 o_peri_pmc5;
    o_peri_pmc5.u32 = gopPMCAllReg->PERI_PMC5.u32;
    o_peri_pmc5.bits.core_avs_hpm_fsm_calc_mode = ucore_avs_hpm_fsm_calc_mode;
    gopPMCAllReg->PERI_PMC5.u32 = o_peri_pmc5.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC5.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC5core_avs_fsm_dec_pwm_step
//  Description : Set the value of the member PERI_PMC5.core_avs_fsm_dec_pwm_step
//  Input       : unsigned int ucore_avs_fsm_dec_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC5core_avs_fsm_dec_pwm_step(unsigned int ucore_avs_fsm_dec_pwm_step)
{
    U_PERI_PMC5 o_peri_pmc5;
    o_peri_pmc5.u32 = gopPMCAllReg->PERI_PMC5.u32;
    o_peri_pmc5.bits.core_avs_fsm_dec_pwm_step = ucore_avs_fsm_dec_pwm_step;
    gopPMCAllReg->PERI_PMC5.u32 = o_peri_pmc5.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC5.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC5core_avs_fsm_inc_pwm_step
//  Description : Set the value of the member PERI_PMC5.core_avs_fsm_inc_pwm_step
//  Input       : unsigned int ucore_avs_fsm_inc_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC5core_avs_fsm_inc_pwm_step(unsigned int ucore_avs_fsm_inc_pwm_step)
{
    U_PERI_PMC5 o_peri_pmc5;
    o_peri_pmc5.u32 = gopPMCAllReg->PERI_PMC5.u32;
    o_peri_pmc5.bits.core_avs_fsm_inc_pwm_step = ucore_avs_fsm_inc_pwm_step;
    gopPMCAllReg->PERI_PMC5.u32 = o_peri_pmc5.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC5.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC6cpu_hpm_fsm_en
//  Description : Set the value of the member PERI_PMC6.cpu_hpm_fsm_en
//  Input       : unsigned int ucpu_hpm_fsm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC6cpu_hpm_fsm_en(unsigned int ucpu_hpm_fsm_en)
{
    U_PERI_PMC6 o_peri_pmc6;
    o_peri_pmc6.u32 = gopPMCAllReg->PERI_PMC6.u32;
    o_peri_pmc6.bits.cpu_hpm_fsm_en = ucpu_hpm_fsm_en;
    gopPMCAllReg->PERI_PMC6.u32 = o_peri_pmc6.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC6.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC6cpu_avs_hpm_fsm_calc_mode
//  Description : Set the value of the member PERI_PMC6.cpu_avs_hpm_fsm_calc_mode
//  Input       : unsigned int ucpu_avs_hpm_fsm_calc_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC6cpu_avs_hpm_fsm_calc_mode(unsigned int ucpu_avs_hpm_fsm_calc_mode)
{
    U_PERI_PMC6 o_peri_pmc6;
    o_peri_pmc6.u32 = gopPMCAllReg->PERI_PMC6.u32;
    o_peri_pmc6.bits.cpu_avs_hpm_fsm_calc_mode = ucpu_avs_hpm_fsm_calc_mode;
    gopPMCAllReg->PERI_PMC6.u32 = o_peri_pmc6.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC6.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC6cpu_avs_fsm_dec_pwm_step
//  Description : Set the value of the member PERI_PMC6.cpu_avs_fsm_dec_pwm_step
//  Input       : unsigned int ucpu_avs_fsm_dec_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC6cpu_avs_fsm_dec_pwm_step(unsigned int ucpu_avs_fsm_dec_pwm_step)
{
    U_PERI_PMC6 o_peri_pmc6;
    o_peri_pmc6.u32 = gopPMCAllReg->PERI_PMC6.u32;
    o_peri_pmc6.bits.cpu_avs_fsm_dec_pwm_step = ucpu_avs_fsm_dec_pwm_step;
    gopPMCAllReg->PERI_PMC6.u32 = o_peri_pmc6.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC6.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC6cpu_avs_fsm_inc_pwm_step
//  Description : Set the value of the member PERI_PMC6.cpu_avs_fsm_inc_pwm_step
//  Input       : unsigned int ucpu_avs_fsm_inc_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC6cpu_avs_fsm_inc_pwm_step(unsigned int ucpu_avs_fsm_inc_pwm_step)
{
    U_PERI_PMC6 o_peri_pmc6;
    o_peri_pmc6.u32 = gopPMCAllReg->PERI_PMC6.u32;
    o_peri_pmc6.bits.cpu_avs_fsm_inc_pwm_step = ucpu_avs_fsm_inc_pwm_step;
    gopPMCAllReg->PERI_PMC6.u32 = o_peri_pmc6.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC6.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC7ddr_hpm_fsm_en
//  Description : Set the value of the member PERI_PMC7.ddr_hpm_fsm_en
//  Input       : unsigned int uddr_hpm_fsm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC7ddr_hpm_fsm_en(unsigned int uddr_hpm_fsm_en)
{
    U_PERI_PMC7 o_peri_pmc7;
    o_peri_pmc7.u32 = gopPMCAllReg->PERI_PMC7.u32;
    o_peri_pmc7.bits.ddr_hpm_fsm_en = uddr_hpm_fsm_en;
    gopPMCAllReg->PERI_PMC7.u32 = o_peri_pmc7.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC7.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC7ddr_avs_hpm_fsm_calc_mode
//  Description : Set the value of the member PERI_PMC7.ddr_avs_hpm_fsm_calc_mode
//  Input       : unsigned int uddr_avs_hpm_fsm_calc_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC7ddr_avs_hpm_fsm_calc_mode(unsigned int uddr_avs_hpm_fsm_calc_mode)
{
    U_PERI_PMC7 o_peri_pmc7;
    o_peri_pmc7.u32 = gopPMCAllReg->PERI_PMC7.u32;
    o_peri_pmc7.bits.ddr_avs_hpm_fsm_calc_mode = uddr_avs_hpm_fsm_calc_mode;
    gopPMCAllReg->PERI_PMC7.u32 = o_peri_pmc7.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC7.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC7ddr_avs_fsm_dec_pwm_step
//  Description : Set the value of the member PERI_PMC7.ddr_avs_fsm_dec_pwm_step
//  Input       : unsigned int uddr_avs_fsm_dec_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC7ddr_avs_fsm_dec_pwm_step(unsigned int uddr_avs_fsm_dec_pwm_step)
{
    U_PERI_PMC7 o_peri_pmc7;
    o_peri_pmc7.u32 = gopPMCAllReg->PERI_PMC7.u32;
    o_peri_pmc7.bits.ddr_avs_fsm_dec_pwm_step = uddr_avs_fsm_dec_pwm_step;
    gopPMCAllReg->PERI_PMC7.u32 = o_peri_pmc7.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC7.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC7ddr_avs_fsm_inc_pwm_step
//  Description : Set the value of the member PERI_PMC7.ddr_avs_fsm_inc_pwm_step
//  Input       : unsigned int uddr_avs_fsm_inc_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC7ddr_avs_fsm_inc_pwm_step(unsigned int uddr_avs_fsm_inc_pwm_step)
{
    U_PERI_PMC7 o_peri_pmc7;
    o_peri_pmc7.u32 = gopPMCAllReg->PERI_PMC7.u32;
    o_peri_pmc7.bits.ddr_avs_fsm_inc_pwm_step = uddr_avs_fsm_inc_pwm_step;
    gopPMCAllReg->PERI_PMC7.u32 = o_peri_pmc7.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC7.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC8mda_hpm_fsm_en
//  Description : Set the value of the member PERI_PMC8.mda_hpm_fsm_en
//  Input       : unsigned int umda_hpm_fsm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC8mda_hpm_fsm_en(unsigned int umda_hpm_fsm_en)
{
    U_PERI_PMC8 o_peri_pmc8;
    o_peri_pmc8.u32 = gopPMCAllReg->PERI_PMC8.u32;
    o_peri_pmc8.bits.mda_hpm_fsm_en = umda_hpm_fsm_en;
    gopPMCAllReg->PERI_PMC8.u32 = o_peri_pmc8.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC8.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC8mda_avs_hpm_fsm_calc_mode
//  Description : Set the value of the member PERI_PMC8.mda_avs_hpm_fsm_calc_mode
//  Input       : unsigned int umda_avs_hpm_fsm_calc_mode: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC8mda_avs_hpm_fsm_calc_mode(unsigned int umda_avs_hpm_fsm_calc_mode)
{
    U_PERI_PMC8 o_peri_pmc8;
    o_peri_pmc8.u32 = gopPMCAllReg->PERI_PMC8.u32;
    o_peri_pmc8.bits.mda_avs_hpm_fsm_calc_mode = umda_avs_hpm_fsm_calc_mode;
    gopPMCAllReg->PERI_PMC8.u32 = o_peri_pmc8.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC8.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC8mda_avs_fsm_dec_pwm_step
//  Description : Set the value of the member PERI_PMC8.mda_avs_fsm_dec_pwm_step
//  Input       : unsigned int umda_avs_fsm_dec_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC8mda_avs_fsm_dec_pwm_step(unsigned int umda_avs_fsm_dec_pwm_step)
{
    U_PERI_PMC8 o_peri_pmc8;
    o_peri_pmc8.u32 = gopPMCAllReg->PERI_PMC8.u32;
    o_peri_pmc8.bits.mda_avs_fsm_dec_pwm_step = umda_avs_fsm_dec_pwm_step;
    gopPMCAllReg->PERI_PMC8.u32 = o_peri_pmc8.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC8.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC8mda_avs_fsm_inc_pwm_step
//  Description : Set the value of the member PERI_PMC8.mda_avs_fsm_inc_pwm_step
//  Input       : unsigned int umda_avs_fsm_inc_pwm_step: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC8mda_avs_fsm_inc_pwm_step(unsigned int umda_avs_fsm_inc_pwm_step)
{
    U_PERI_PMC8 o_peri_pmc8;
    o_peri_pmc8.u32 = gopPMCAllReg->PERI_PMC8.u32;
    o_peri_pmc8.bits.mda_avs_fsm_inc_pwm_step = umda_avs_fsm_inc_pwm_step;
    gopPMCAllReg->PERI_PMC8.u32 = o_peri_pmc8.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC8.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_div
//  Description : Set the value of the member PERI_PMC10.core_hpm_div
//  Input       : unsigned int ucore_hpm_div: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_div(unsigned int ucore_hpm_div)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_div = ucore_hpm_div;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_shift
//  Description : Set the value of the member PERI_PMC10.core_hpm_shift
//  Input       : unsigned int ucore_hpm_shift: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_shift(unsigned int ucore_hpm_shift)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_shift = ucore_hpm_shift;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_offset
//  Description : Set the value of the member PERI_PMC10.core_hpm_offset
//  Input       : unsigned int ucore_hpm_offset: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_offset(unsigned int ucore_hpm_offset)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_offset = ucore_hpm_offset;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_en
//  Description : Set the value of the member PERI_PMC10.core_hpm_en
//  Input       : unsigned int ucore_hpm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_en(unsigned int ucore_hpm_en)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_en = ucore_hpm_en;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_bypass
//  Description : Set the value of the member PERI_PMC10.core_hpm_bypass
//  Input       : unsigned int ucore_hpm_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_bypass(unsigned int ucore_hpm_bypass)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_bypass = ucore_hpm_bypass;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_monitor_en
//  Description : Set the value of the member PERI_PMC10.core_hpm_monitor_en
//  Input       : unsigned int ucore_hpm_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_monitor_en(unsigned int ucore_hpm_monitor_en)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_monitor_en = ucore_hpm_monitor_en;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC10core_hpm_srst_req
//  Description : Set the value of the member PERI_PMC10.core_hpm_srst_req
//  Input       : unsigned int ucore_hpm_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC10core_hpm_srst_req(unsigned int ucore_hpm_srst_req)
{
    U_PERI_PMC10 o_peri_pmc10;
    o_peri_pmc10.u32 = gopPMCAllReg->PERI_PMC10.u32;
    o_peri_pmc10.bits.core_hpm_srst_req = ucore_hpm_srst_req;
    gopPMCAllReg->PERI_PMC10.u32 = o_peri_pmc10.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC10.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC13core_hpm_uplimit
//  Description : Set the value of the member PERI_PMC13.core_hpm_uplimit
//  Input       : unsigned int ucore_hpm_uplimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC13core_hpm_uplimit(unsigned int ucore_hpm_uplimit)
{
    U_PERI_PMC13 o_peri_pmc13;
    o_peri_pmc13.u32 = gopPMCAllReg->PERI_PMC13.u32;
    o_peri_pmc13.bits.core_hpm_uplimit = ucore_hpm_uplimit;
    gopPMCAllReg->PERI_PMC13.u32 = o_peri_pmc13.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC13.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC13core_hpm_lowlimit
//  Description : Set the value of the member PERI_PMC13.core_hpm_lowlimit
//  Input       : unsigned int ucore_hpm_lowlimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC13core_hpm_lowlimit(unsigned int ucore_hpm_lowlimit)
{
    U_PERI_PMC13 o_peri_pmc13;
    o_peri_pmc13.u32 = gopPMCAllReg->PERI_PMC13.u32;
    o_peri_pmc13.bits.core_hpm_lowlimit = ucore_hpm_lowlimit;
    gopPMCAllReg->PERI_PMC13.u32 = o_peri_pmc13.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC13.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC13core_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC13.core_hpm_monitor_period
//  Input       : unsigned int ucore_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC13core_hpm_monitor_period(unsigned int ucore_hpm_monitor_period)
{
    U_PERI_PMC13 o_peri_pmc13;
    o_peri_pmc13.u32 = gopPMCAllReg->PERI_PMC13.u32;
    o_peri_pmc13.bits.core_hpm_monitor_period = ucore_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC13.u32 = o_peri_pmc13.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC13.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_div
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_div
//  Input       : unsigned int ucpu_hpm_div: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_div(unsigned int ucpu_hpm_div)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_div = ucpu_hpm_div;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_shift
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_shift
//  Input       : unsigned int ucpu_hpm_shift: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_shift(unsigned int ucpu_hpm_shift)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_shift = ucpu_hpm_shift;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_offset
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_offset
//  Input       : unsigned int ucpu_hpm_offset: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_offset(unsigned int ucpu_hpm_offset)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_offset = ucpu_hpm_offset;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_en
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_en
//  Input       : unsigned int ucpu_hpm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_en(unsigned int ucpu_hpm_en)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_en = ucpu_hpm_en;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_bypass
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_bypass
//  Input       : unsigned int ucpu_hpm_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_bypass(unsigned int ucpu_hpm_bypass)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_bypass = ucpu_hpm_bypass;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_monitor_en
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_monitor_en
//  Input       : unsigned int ucpu_hpm_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_monitor_en(unsigned int ucpu_hpm_monitor_en)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_monitor_en = ucpu_hpm_monitor_en;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC14cpu_hpm_srst_req
//  Description : Set the value of the member PERI_PMC14.cpu_hpm_srst_req
//  Input       : unsigned int ucpu_hpm_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC14cpu_hpm_srst_req(unsigned int ucpu_hpm_srst_req)
{
    U_PERI_PMC14 o_peri_pmc14;
    o_peri_pmc14.u32 = gopPMCAllReg->PERI_PMC14.u32;
    o_peri_pmc14.bits.cpu_hpm_srst_req = ucpu_hpm_srst_req;
    gopPMCAllReg->PERI_PMC14.u32 = o_peri_pmc14.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC14.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC17cpu_hpm_uplimit
//  Description : Set the value of the member PERI_PMC17.cpu_hpm_uplimit
//  Input       : unsigned int ucpu_hpm_uplimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC17cpu_hpm_uplimit(unsigned int ucpu_hpm_uplimit)
{
    U_PERI_PMC17 o_peri_pmc17;
    o_peri_pmc17.u32 = gopPMCAllReg->PERI_PMC17.u32;
    o_peri_pmc17.bits.cpu_hpm_uplimit = ucpu_hpm_uplimit;
    gopPMCAllReg->PERI_PMC17.u32 = o_peri_pmc17.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC17.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC17cpu_hpm_lowlimit
//  Description : Set the value of the member PERI_PMC17.cpu_hpm_lowlimit
//  Input       : unsigned int ucpu_hpm_lowlimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC17cpu_hpm_lowlimit(unsigned int ucpu_hpm_lowlimit)
{
    U_PERI_PMC17 o_peri_pmc17;
    o_peri_pmc17.u32 = gopPMCAllReg->PERI_PMC17.u32;
    o_peri_pmc17.bits.cpu_hpm_lowlimit = ucpu_hpm_lowlimit;
    gopPMCAllReg->PERI_PMC17.u32 = o_peri_pmc17.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC17.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC17cpu_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC17.cpu_hpm_monitor_period
//  Input       : unsigned int ucpu_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC17cpu_hpm_monitor_period(unsigned int ucpu_hpm_monitor_period)
{     
    U_PERI_PMC17 o_peri_pmc17;
    o_peri_pmc17.u32 = gopPMCAllReg->PERI_PMC17.u32;
    o_peri_pmc17.bits.cpu_hpm_monitor_period = ucpu_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC17.u32 = o_peri_pmc17.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC17.u32));
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_div
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_div
//  Input       : unsigned int uddr_hpm_div: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_div(unsigned int uddr_hpm_div)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_div = uddr_hpm_div;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_shift
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_shift
//  Input       : unsigned int uddr_hpm_shift: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_shift(unsigned int uddr_hpm_shift)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_shift = uddr_hpm_shift;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_offset
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_offset
//  Input       : unsigned int uddr_hpm_offset: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_offset(unsigned int uddr_hpm_offset)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_offset = uddr_hpm_offset;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_en
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_en
//  Input       : unsigned int uddr_hpm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_en(unsigned int uddr_hpm_en)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_en = uddr_hpm_en;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_bypass
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_bypass
//  Input       : unsigned int uddr_hpm_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_bypass(unsigned int uddr_hpm_bypass)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_bypass = uddr_hpm_bypass;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_monitor_en
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_monitor_en
//  Input       : unsigned int uddr_hpm_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_monitor_en(unsigned int uddr_hpm_monitor_en)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_monitor_en = uddr_hpm_monitor_en;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC18ddr_hpm_srst_req
//  Description : Set the value of the member PERI_PMC18.ddr_hpm_srst_req
//  Input       : unsigned int uddr_hpm_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC18ddr_hpm_srst_req(unsigned int uddr_hpm_srst_req)
{
    U_PERI_PMC18 o_peri_pmc18;
    o_peri_pmc18.u32 = gopPMCAllReg->PERI_PMC18.u32;
    o_peri_pmc18.bits.ddr_hpm_srst_req = uddr_hpm_srst_req;
    gopPMCAllReg->PERI_PMC18.u32 = o_peri_pmc18.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC18.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC21ddr_hpm_uplimit
//  Description : Set the value of the member PERI_PMC21.ddr_hpm_uplimit
//  Input       : unsigned int uddr_hpm_uplimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC21ddr_hpm_uplimit(unsigned int uddr_hpm_uplimit)
{
    U_PERI_PMC21 o_peri_pmc21;
    o_peri_pmc21.u32 = gopPMCAllReg->PERI_PMC21.u32;
    o_peri_pmc21.bits.ddr_hpm_uplimit = uddr_hpm_uplimit;
    gopPMCAllReg->PERI_PMC21.u32 = o_peri_pmc21.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC21.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC21ddr_hpm_lowlimit
//  Description : Set the value of the member PERI_PMC21.ddr_hpm_lowlimit
//  Input       : unsigned int uddr_hpm_lowlimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC21ddr_hpm_lowlimit(unsigned int uddr_hpm_lowlimit)
{
    U_PERI_PMC21 o_peri_pmc21;
    o_peri_pmc21.u32 = gopPMCAllReg->PERI_PMC21.u32;
    o_peri_pmc21.bits.ddr_hpm_lowlimit = uddr_hpm_lowlimit;
    gopPMCAllReg->PERI_PMC21.u32 = o_peri_pmc21.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC21.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC21ddr_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC21.ddr_hpm_monitor_period
//  Input       : unsigned int uddr_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC21ddr_hpm_monitor_period(unsigned int uddr_hpm_monitor_period)
{
    U_PERI_PMC21 o_peri_pmc21;
    o_peri_pmc21.u32 = gopPMCAllReg->PERI_PMC21.u32;
    o_peri_pmc21.bits.ddr_hpm_monitor_period = uddr_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC21.u32 = o_peri_pmc21.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC21.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_div
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_div
//  Input       : unsigned int umda_top_hpm_div: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_div(unsigned int umda_top_hpm_div)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_div = umda_top_hpm_div;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_shift
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_shift
//  Input       : unsigned int umda_top_hpm_shift: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_shift(unsigned int umda_top_hpm_shift)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_shift = umda_top_hpm_shift;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_offset
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_offset
//  Input       : unsigned int umda_top_hpm_offset: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_offset(unsigned int umda_top_hpm_offset)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_offset = umda_top_hpm_offset;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_en
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_en
//  Input       : unsigned int umda_top_hpm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_en(unsigned int umda_top_hpm_en)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_en = umda_top_hpm_en;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_bypass
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_bypass
//  Input       : unsigned int umda_top_hpm_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_bypass(unsigned int umda_top_hpm_bypass)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_bypass = umda_top_hpm_bypass;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_monitor_en
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_monitor_en
//  Input       : unsigned int umda_top_hpm_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_monitor_en(unsigned int umda_top_hpm_monitor_en)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_monitor_en = umda_top_hpm_monitor_en;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC22mda_top_hpm_srst_req
//  Description : Set the value of the member PERI_PMC22.mda_top_hpm_srst_req
//  Input       : unsigned int umda_top_hpm_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC22mda_top_hpm_srst_req(unsigned int umda_top_hpm_srst_req)
{
    U_PERI_PMC22 o_peri_pmc22;
    o_peri_pmc22.u32 = gopPMCAllReg->PERI_PMC22.u32;
    o_peri_pmc22.bits.mda_top_hpm_srst_req = umda_top_hpm_srst_req;
    gopPMCAllReg->PERI_PMC22.u32 = o_peri_pmc22.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC22.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC25mda_top_hpm_uplimit
//  Description : Set the value of the member PERI_PMC25.mda_top_hpm_uplimit
//  Input       : unsigned int umda_top_hpm_uplimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC25mda_top_hpm_uplimit(unsigned int umda_top_hpm_uplimit)
{
    U_PERI_PMC25 o_peri_pmc25;
    o_peri_pmc25.u32 = gopPMCAllReg->PERI_PMC25.u32;
    o_peri_pmc25.bits.mda_top_hpm_uplimit = umda_top_hpm_uplimit;
    gopPMCAllReg->PERI_PMC25.u32 = o_peri_pmc25.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC25.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC25mda_top_hpm_lowlimit
//  Description : Set the value of the member PERI_PMC25.mda_top_hpm_lowlimit
//  Input       : unsigned int umda_top_hpm_lowlimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC25mda_top_hpm_lowlimit(unsigned int umda_top_hpm_lowlimit)
{
    U_PERI_PMC25 o_peri_pmc25;
    o_peri_pmc25.u32 = gopPMCAllReg->PERI_PMC25.u32;
    o_peri_pmc25.bits.mda_top_hpm_lowlimit = umda_top_hpm_lowlimit;
    gopPMCAllReg->PERI_PMC25.u32 = o_peri_pmc25.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC25.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC25mda_top_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC25.mda_top_hpm_monitor_period
//  Input       : unsigned int umda_top_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC25mda_top_hpm_monitor_period(unsigned int umda_top_hpm_monitor_period)
{
    U_PERI_PMC25 o_peri_pmc25;
    o_peri_pmc25.u32 = gopPMCAllReg->PERI_PMC25.u32;
    o_peri_pmc25.bits.mda_top_hpm_monitor_period = umda_top_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC25.u32 = o_peri_pmc25.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC25.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_div
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_div
//  Input       : unsigned int uvedu_hpm_div: 6 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_div(unsigned int uvedu_hpm_div)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_div = uvedu_hpm_div;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_shift
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_shift
//  Input       : unsigned int uvedu_hpm_shift: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_shift(unsigned int uvedu_hpm_shift)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_shift = uvedu_hpm_shift;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_offset
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_offset
//  Input       : unsigned int uvedu_hpm_offset: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_offset(unsigned int uvedu_hpm_offset)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_offset = uvedu_hpm_offset;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_en
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_en
//  Input       : unsigned int uvedu_hpm_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_en(unsigned int uvedu_hpm_en)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_en = uvedu_hpm_en;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_bypass
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_bypass
//  Input       : unsigned int uvedu_hpm_bypass: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_bypass(unsigned int uvedu_hpm_bypass)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_bypass = uvedu_hpm_bypass;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_monitor_en
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_monitor_en
//  Input       : unsigned int uvedu_hpm_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_monitor_en(unsigned int uvedu_hpm_monitor_en)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_monitor_en = uvedu_hpm_monitor_en;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC26vedu_hpm_srst_req
//  Description : Set the value of the member PERI_PMC26.vedu_hpm_srst_req
//  Input       : unsigned int uvedu_hpm_srst_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC26vedu_hpm_srst_req(unsigned int uvedu_hpm_srst_req)
{
    U_PERI_PMC26 o_peri_pmc26;
    o_peri_pmc26.u32 = gopPMCAllReg->PERI_PMC26.u32;
    o_peri_pmc26.bits.vedu_hpm_srst_req = uvedu_hpm_srst_req;
    gopPMCAllReg->PERI_PMC26.u32 = o_peri_pmc26.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC26.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC29vedu_hpm_uplimit
//  Description : Set the value of the member PERI_PMC29.vedu_hpm_uplimit
//  Input       : unsigned int uvedu_hpm_uplimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC29vedu_hpm_uplimit(unsigned int uvedu_hpm_uplimit)
{
    U_PERI_PMC29 o_peri_pmc29;
    o_peri_pmc29.u32 = gopPMCAllReg->PERI_PMC29.u32;
    o_peri_pmc29.bits.vedu_hpm_uplimit = uvedu_hpm_uplimit;
    gopPMCAllReg->PERI_PMC29.u32 = o_peri_pmc29.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC29.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC29vedu_hpm_lowlimit
//  Description : Set the value of the member PERI_PMC29.vedu_hpm_lowlimit
//  Input       : unsigned int uvedu_hpm_lowlimit: 10 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC29vedu_hpm_lowlimit(unsigned int uvedu_hpm_lowlimit)
{
    U_PERI_PMC29 o_peri_pmc29;
    o_peri_pmc29.u32 = gopPMCAllReg->PERI_PMC29.u32;
    o_peri_pmc29.bits.vedu_hpm_lowlimit = uvedu_hpm_lowlimit;
    gopPMCAllReg->PERI_PMC29.u32 = o_peri_pmc29.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC29.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC29vedu_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC29.vedu_hpm_monitor_period
//  Input       : unsigned int uvedu_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC29vedu_hpm_monitor_period(unsigned int uvedu_hpm_monitor_period)
{
    U_PERI_PMC29 o_peri_pmc29;
    o_peri_pmc29.u32 = gopPMCAllReg->PERI_PMC29.u32;
    o_peri_pmc29.bits.vedu_hpm_monitor_period = uvedu_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC29.u32 = o_peri_pmc29.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC29.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC30vedu_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC30.vedu_hpm_monitor_period
//  Input       : unsigned int uvedu_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC30vedu_hpm_monitor_period(unsigned int uvedu_hpm_monitor_period)
{
    U_PERI_PMC30 o_peri_pmc30;
    o_peri_pmc30.u32 = gopPMCAllReg->PERI_PMC30.u32;
    o_peri_pmc30.bits.vedu_hpm_monitor_period = uvedu_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC30.u32 = o_peri_pmc30.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC30.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC30mda_top_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC30.mda_top_hpm_monitor_period
//  Input       : unsigned int umda_top_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC30mda_top_hpm_monitor_period(unsigned int umda_top_hpm_monitor_period)
{
    U_PERI_PMC30 o_peri_pmc30;
    o_peri_pmc30.u32 = gopPMCAllReg->PERI_PMC30.u32;
    o_peri_pmc30.bits.mda_top_hpm_monitor_period = umda_top_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC30.u32 = o_peri_pmc30.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC30.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC30ddr_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC30.ddr_hpm_monitor_period
//  Input       : unsigned int uddr_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC30ddr_hpm_monitor_period(unsigned int uddr_hpm_monitor_period)
{
    U_PERI_PMC30 o_peri_pmc30;
    o_peri_pmc30.u32 = gopPMCAllReg->PERI_PMC30.u32;
    o_peri_pmc30.bits.ddr_hpm_monitor_period = uddr_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC30.u32 = o_peri_pmc30.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC30.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC30cpu_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC30.cpu_hpm_monitor_period
//  Input       : unsigned int ucpu_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC30cpu_hpm_monitor_period(unsigned int ucpu_hpm_monitor_period)
{
    U_PERI_PMC30 o_peri_pmc30;
    
    o_peri_pmc30.u32 = gopPMCAllReg->PERI_PMC30.u32;
    o_peri_pmc30.bits.cpu_hpm_monitor_period = ucpu_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC30.u32 = o_peri_pmc30.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC30.u32));
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC31core_hpm_monitor_period
//  Description : Set the value of the member PERI_PMC31.core_hpm_monitor_period
//  Input       : unsigned int ucore_hpm_monitor_period: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC31core_hpm_monitor_period(unsigned int ucore_hpm_monitor_period)
{
    U_PERI_PMC31 o_peri_pmc31;
    o_peri_pmc31.u32 = gopPMCAllReg->PERI_PMC31.u32;
    o_peri_pmc31.bits.core_hpm_monitor_period = ucore_hpm_monitor_period;
    gopPMCAllReg->PERI_PMC31.u32 = o_peri_pmc31.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC31.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC32cpu_ts_sel
//  Description : Set the value of the member PERI_PMC32.cpu_ts_sel
//  Input       : unsigned int ucpu_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC32cpu_ts_sel(unsigned int ucpu_ts_sel)
{
    U_PERI_PMC32 o_peri_pmc32;
    o_peri_pmc32.u32 = gopPMCAllReg->PERI_PMC32.u32;
    o_peri_pmc32.bits.cpu_ts_sel = ucpu_ts_sel;
    gopPMCAllReg->PERI_PMC32.u32 = o_peri_pmc32.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC32.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC32cpu_ts_dly_adjust
//  Description : Set the value of the member PERI_PMC32.cpu_ts_dly_adjust
//  Input       : unsigned int ucpu_ts_dly_adjust: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC32cpu_ts_dly_adjust(unsigned int ucpu_ts_dly_adjust)
{
    U_PERI_PMC32 o_peri_pmc32;
    o_peri_pmc32.u32 = gopPMCAllReg->PERI_PMC32.u32;
    o_peri_pmc32.bits.cpu_ts_dly_adjust = ucpu_ts_dly_adjust;
    gopPMCAllReg->PERI_PMC32.u32 = o_peri_pmc32.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC32.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC32cpu_ts_step
//  Description : Set the value of the member PERI_PMC32.cpu_ts_step
//  Input       : unsigned int ucpu_ts_step: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC32cpu_ts_step(unsigned int ucpu_ts_step)
{
    U_PERI_PMC32 o_peri_pmc32;
    o_peri_pmc32.u32 = gopPMCAllReg->PERI_PMC32.u32;
    o_peri_pmc32.bits.cpu_ts_step = ucpu_ts_step;
    gopPMCAllReg->PERI_PMC32.u32 = o_peri_pmc32.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC32.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC32cpu_ts_en
//  Description : Set the value of the member PERI_PMC32.cpu_ts_en
//  Input       : unsigned int ucpu_ts_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC32cpu_ts_en(unsigned int ucpu_ts_en)
{
    U_PERI_PMC32 o_peri_pmc32;
    o_peri_pmc32.u32 = gopPMCAllReg->PERI_PMC32.u32;
    o_peri_pmc32.bits.cpu_ts_en = ucpu_ts_en;
    gopPMCAllReg->PERI_PMC32.u32 = o_peri_pmc32.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC32.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC33ddr_ts_sel
//  Description : Set the value of the member PERI_PMC33.ddr_ts_sel
//  Input       : unsigned int uddr_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC33ddr_ts_sel(unsigned int uddr_ts_sel)
{
    U_PERI_PMC33 o_peri_pmc33;
    o_peri_pmc33.u32 = gopPMCAllReg->PERI_PMC33.u32;
    o_peri_pmc33.bits.ddr_ts_sel = uddr_ts_sel;
    gopPMCAllReg->PERI_PMC33.u32 = o_peri_pmc33.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC33.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC33ddr_ts_dly_adjust
//  Description : Set the value of the member PERI_PMC33.ddr_ts_dly_adjust
//  Input       : unsigned int uddr_ts_dly_adjust: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC33ddr_ts_dly_adjust(unsigned int uddr_ts_dly_adjust)
{
    U_PERI_PMC33 o_peri_pmc33;
    o_peri_pmc33.u32 = gopPMCAllReg->PERI_PMC33.u32;
    o_peri_pmc33.bits.ddr_ts_dly_adjust = uddr_ts_dly_adjust;
    gopPMCAllReg->PERI_PMC33.u32 = o_peri_pmc33.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC33.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC33ddr_ts_step
//  Description : Set the value of the member PERI_PMC33.ddr_ts_step
//  Input       : unsigned int uddr_ts_step: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC33ddr_ts_step(unsigned int uddr_ts_step)
{
    U_PERI_PMC33 o_peri_pmc33;
    o_peri_pmc33.u32 = gopPMCAllReg->PERI_PMC33.u32;
    o_peri_pmc33.bits.ddr_ts_step = uddr_ts_step;
    gopPMCAllReg->PERI_PMC33.u32 = o_peri_pmc33.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC33.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC33ddr_ts_en
//  Description : Set the value of the member PERI_PMC33.ddr_ts_en
//  Input       : unsigned int uddr_ts_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC33ddr_ts_en(unsigned int uddr_ts_en)
{
    U_PERI_PMC33 o_peri_pmc33;
    o_peri_pmc33.u32 = gopPMCAllReg->PERI_PMC33.u32;
    o_peri_pmc33.bits.ddr_ts_en = uddr_ts_en;
    gopPMCAllReg->PERI_PMC33.u32 = o_peri_pmc33.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC33.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC34core_ts_sel
//  Description : Set the value of the member PERI_PMC34.core_ts_sel
//  Input       : unsigned int ucore_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC34core_ts_sel(unsigned int ucore_ts_sel)
{
    U_PERI_PMC34 o_peri_pmc34;
    o_peri_pmc34.u32 = gopPMCAllReg->PERI_PMC34.u32;
    o_peri_pmc34.bits.core_ts_sel = ucore_ts_sel;
    gopPMCAllReg->PERI_PMC34.u32 = o_peri_pmc34.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC34.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC34core_ts_dly_adjust
//  Description : Set the value of the member PERI_PMC34.core_ts_dly_adjust
//  Input       : unsigned int ucore_ts_dly_adjust: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC34core_ts_dly_adjust(unsigned int ucore_ts_dly_adjust)
{
    U_PERI_PMC34 o_peri_pmc34;
    o_peri_pmc34.u32 = gopPMCAllReg->PERI_PMC34.u32;
    o_peri_pmc34.bits.core_ts_dly_adjust = ucore_ts_dly_adjust;
    gopPMCAllReg->PERI_PMC34.u32 = o_peri_pmc34.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC34.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC34core_ts_step
//  Description : Set the value of the member PERI_PMC34.core_ts_step
//  Input       : unsigned int ucore_ts_step: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC34core_ts_step(unsigned int ucore_ts_step)
{
    U_PERI_PMC34 o_peri_pmc34;
    o_peri_pmc34.u32 = gopPMCAllReg->PERI_PMC34.u32;
    o_peri_pmc34.bits.core_ts_step = ucore_ts_step;
    gopPMCAllReg->PERI_PMC34.u32 = o_peri_pmc34.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC34.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC34core_ts_en
//  Description : Set the value of the member PERI_PMC34.core_ts_en
//  Input       : unsigned int ucore_ts_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC34core_ts_en(unsigned int ucore_ts_en)
{
    U_PERI_PMC34 o_peri_pmc34;
    o_peri_pmc34.u32 = gopPMCAllReg->PERI_PMC34.u32;
    o_peri_pmc34.bits.core_ts_en = ucore_ts_en;
    gopPMCAllReg->PERI_PMC34.u32 = o_peri_pmc34.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC34.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC35mda_top_ts_sel
//  Description : Set the value of the member PERI_PMC35.mda_top_ts_sel
//  Input       : unsigned int umda_top_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC35mda_top_ts_sel(unsigned int umda_top_ts_sel)
{
    U_PERI_PMC35 o_peri_pmc35;
    o_peri_pmc35.u32 = gopPMCAllReg->PERI_PMC35.u32;
    o_peri_pmc35.bits.mda_top_ts_sel = umda_top_ts_sel;
    gopPMCAllReg->PERI_PMC35.u32 = o_peri_pmc35.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC35.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC35mda_top_ts_dly_adjust
//  Description : Set the value of the member PERI_PMC35.mda_top_ts_dly_adjust
//  Input       : unsigned int umda_top_ts_dly_adjust: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC35mda_top_ts_dly_adjust(unsigned int umda_top_ts_dly_adjust)
{
    U_PERI_PMC35 o_peri_pmc35;
    o_peri_pmc35.u32 = gopPMCAllReg->PERI_PMC35.u32;
    o_peri_pmc35.bits.mda_top_ts_dly_adjust = umda_top_ts_dly_adjust;
    gopPMCAllReg->PERI_PMC35.u32 = o_peri_pmc35.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC35.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC35mda_top_ts_step
//  Description : Set the value of the member PERI_PMC35.mda_top_ts_step
//  Input       : unsigned int umda_top_ts_step: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC35mda_top_ts_step(unsigned int umda_top_ts_step)
{
    U_PERI_PMC35 o_peri_pmc35;
    o_peri_pmc35.u32 = gopPMCAllReg->PERI_PMC35.u32;
    o_peri_pmc35.bits.mda_top_ts_step = umda_top_ts_step;
    gopPMCAllReg->PERI_PMC35.u32 = o_peri_pmc35.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC35.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC35mda_top_ts_en
//  Description : Set the value of the member PERI_PMC35.mda_top_ts_en
//  Input       : unsigned int umda_top_ts_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC35mda_top_ts_en(unsigned int umda_top_ts_en)
{
    U_PERI_PMC35 o_peri_pmc35;
    o_peri_pmc35.u32 = gopPMCAllReg->PERI_PMC35.u32;
    o_peri_pmc35.bits.mda_top_ts_en = umda_top_ts_en;
    gopPMCAllReg->PERI_PMC35.u32 = o_peri_pmc35.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC35.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC36vedu_ts_sel
//  Description : Set the value of the member PERI_PMC36.vedu_ts_sel
//  Input       : unsigned int uvedu_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC36vedu_ts_sel(unsigned int uvedu_ts_sel)
{
    U_PERI_PMC36 o_peri_pmc36;
    o_peri_pmc36.u32 = gopPMCAllReg->PERI_PMC36.u32;
    o_peri_pmc36.bits.vedu_ts_sel = uvedu_ts_sel;
    gopPMCAllReg->PERI_PMC36.u32 = o_peri_pmc36.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC36.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC36vedu_ts_dly_adjust
//  Description : Set the value of the member PERI_PMC36.vedu_ts_dly_adjust
//  Input       : unsigned int uvedu_ts_dly_adjust: 4 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC36vedu_ts_dly_adjust(unsigned int uvedu_ts_dly_adjust)
{
    U_PERI_PMC36 o_peri_pmc36;
    o_peri_pmc36.u32 = gopPMCAllReg->PERI_PMC36.u32;
    o_peri_pmc36.bits.vedu_ts_dly_adjust = uvedu_ts_dly_adjust;
    gopPMCAllReg->PERI_PMC36.u32 = o_peri_pmc36.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC36.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC36vedu_ts_step
//  Description : Set the value of the member PERI_PMC36.vedu_ts_step
//  Input       : unsigned int uvedu_ts_step: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC36vedu_ts_step(unsigned int uvedu_ts_step)
{
    U_PERI_PMC36 o_peri_pmc36;
    o_peri_pmc36.u32 = gopPMCAllReg->PERI_PMC36.u32;
    o_peri_pmc36.bits.vedu_ts_step = uvedu_ts_step;
    gopPMCAllReg->PERI_PMC36.u32 = o_peri_pmc36.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC36.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC36vedu_ts_en
//  Description : Set the value of the member PERI_PMC36.vedu_ts_en
//  Input       : unsigned int uvedu_ts_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC36vedu_ts_en(unsigned int uvedu_ts_en)
{
    U_PERI_PMC36 o_peri_pmc36;
    o_peri_pmc36.u32 = gopPMCAllReg->PERI_PMC36.u32;
    o_peri_pmc36.bits.vedu_ts_en = uvedu_ts_en;
    gopPMCAllReg->PERI_PMC36.u32 = o_peri_pmc36.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC36.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_addr
//  Description : Set the value of the member PERI_PMC58.pmu_addr
//  Input       : unsigned int upmu_addr: 7 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_addr(unsigned int upmu_addr)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_addr = upmu_addr;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg_rd_all
//  Description : Set the value of the member PERI_PMC58.pmu_reg_rd_all
//  Input       : unsigned int upmu_reg_rd_all: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg_rd_all(unsigned int upmu_reg_rd_all)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg_rd_all = upmu_reg_rd_all;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}
int iGetPERI_PMC58pmu_reg_rd_all(unsigned int *upmu_reg_rd_all)
{
    *upmu_reg_rd_all = gopPMCAllReg->PERI_PMC58.bits.pmu_reg_rd_all;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg0_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg0_wt_req
//  Input       : unsigned int upmu_reg0_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg0_wt_req(unsigned int upmu_reg0_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg0_wt_req = upmu_reg0_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg1_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg1_wt_req
//  Input       : unsigned int upmu_reg1_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg1_wt_req(unsigned int upmu_reg1_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg1_wt_req = upmu_reg1_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg2_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg2_wt_req
//  Input       : unsigned int upmu_reg2_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg2_wt_req(unsigned int upmu_reg2_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg2_wt_req = upmu_reg2_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg3_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg3_wt_req
//  Input       : unsigned int upmu_reg3_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg3_wt_req(unsigned int upmu_reg3_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg3_wt_req = upmu_reg3_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}
int iGetPERI_PMC58pmu_reg3_wt_req(unsigned int *upmu_reg3_wt_req)
{
    *upmu_reg3_wt_req = gopPMCAllReg->PERI_PMC58.bits.pmu_reg3_wt_req;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg4_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg4_wt_req
//  Input       : unsigned int upmu_reg4_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg4_wt_req(unsigned int upmu_reg4_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg4_wt_req = upmu_reg4_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}
int iGetPERI_PMC58pmu_reg4_wt_req(unsigned int *upmu_reg4_wt_req)
{
    *upmu_reg4_wt_req = gopPMCAllReg->PERI_PMC58.bits.pmu_reg4_wt_req;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg5_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg5_wt_req
//  Input       : unsigned int upmu_reg5_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg5_wt_req(unsigned int upmu_reg5_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg5_wt_req = upmu_reg5_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}
int iGetPERI_PMC58pmu_reg5_wt_req(unsigned int *upmu_reg5_wt_req)
{
    *upmu_reg5_wt_req = gopPMCAllReg->PERI_PMC58.bits.pmu_reg5_wt_req;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg6_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg6_wt_req
//  Input       : unsigned int upmu_reg6_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg6_wt_req(unsigned int upmu_reg6_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg6_wt_req = upmu_reg6_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmu_reg7_wt_req
//  Description : Set the value of the member PERI_PMC58.pmu_reg7_wt_req
//  Input       : unsigned int upmu_reg7_wt_req: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmu_reg7_wt_req(unsigned int upmu_reg7_wt_req)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmu_reg7_wt_req = upmu_reg7_wt_req;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

int iGetPERI_PMC58pmu_reg7_wt_req(unsigned int *upmu_reg7_wt_req)
{
    *upmu_reg7_wt_req = gopPMCAllReg->PERI_PMC58.bits.pmu_reg7_wt_req;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58i2c_int_clear
//  Description : Set the value of the member PERI_PMC58.i2c_int_clear
//  Input       : unsigned int ui2c_int_clear: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58i2c_int_clear(unsigned int ui2c_int_clear)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.i2c_int_clear = ui2c_int_clear;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC58pmc_i2c_enable
//  Description : Set the value of the member PERI_PMC58.pmc_i2c_enable
//  Input       : unsigned int upmc_i2c_enable: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC58pmc_i2c_enable(unsigned int upmc_i2c_enable)
{
    U_PERI_PMC58 o_peri_pmc58;
    o_peri_pmc58.u32 = gopPMCAllReg->PERI_PMC58.u32;
    o_peri_pmc58.bits.pmc_i2c_enable = upmc_i2c_enable;
    gopPMCAllReg->PERI_PMC58.u32 = o_peri_pmc58.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC58.u32));

    return 1;
}

int iGetPERI_PMC58pmc_i2c_enable(unsigned int *upmc_i2c_enable)
{
    *upmc_i2c_enable = gopPMCAllReg->PERI_PMC58.bits.pmc_i2c_enable;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC59pmu_reg0
//  Description : Set the value of the member PERI_PMC59.pmu_reg0
//  Input       : unsigned int upmu_reg0: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC59pmu_reg0(unsigned int upmu_reg0)
{
    U_PERI_PMC59 o_peri_pmc59;
    o_peri_pmc59.u32 = gopPMCAllReg->PERI_PMC59.u32;
    o_peri_pmc59.bits.pmu_reg0 = upmu_reg0;
    gopPMCAllReg->PERI_PMC59.u32 = o_peri_pmc59.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC59.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC59pmu_reg1
//  Description : Set the value of the member PERI_PMC59.pmu_reg1
//  Input       : unsigned int upmu_reg1: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC59pmu_reg1(unsigned int upmu_reg1)
{
    U_PERI_PMC59 o_peri_pmc59;
    o_peri_pmc59.u32 = gopPMCAllReg->PERI_PMC59.u32;
    o_peri_pmc59.bits.pmu_reg1 = upmu_reg1;
    gopPMCAllReg->PERI_PMC59.u32 = o_peri_pmc59.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC59.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC59pmu_reg2
//  Description : Set the value of the member PERI_PMC59.pmu_reg2
//  Input       : unsigned int upmu_reg2: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC59pmu_reg2(unsigned int upmu_reg2)
{
    U_PERI_PMC59 o_peri_pmc59;
    o_peri_pmc59.u32 = gopPMCAllReg->PERI_PMC59.u32;
    o_peri_pmc59.bits.pmu_reg2 = upmu_reg2;
    gopPMCAllReg->PERI_PMC59.u32 = o_peri_pmc59.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC59.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC59pmu_reg3
//  Description : Set the value of the member PERI_PMC59.pmu_reg3
//  Input       : unsigned int upmu_reg3: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC59pmu_reg3(unsigned int upmu_reg3)
{
    U_PERI_PMC59 o_peri_pmc59;
    o_peri_pmc59.u32 = gopPMCAllReg->PERI_PMC59.u32;
    o_peri_pmc59.bits.pmu_reg3 = upmu_reg3;
    gopPMCAllReg->PERI_PMC59.u32 = o_peri_pmc59.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC59.u32));

    return 1;
}
int iGetPERI_PMC59pmu_reg3(unsigned int *upmu_reg3)
{
    *upmu_reg3 = gopPMCAllReg->PERI_PMC59.bits.pmu_reg3;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC60pmu_reg4
//  Description : Set the value of the member PERI_PMC60.pmu_reg4
//  Input       : unsigned int upmu_reg4: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC60pmu_reg4(unsigned int upmu_reg4)
{
    U_PERI_PMC60 o_peri_pmc60;
    o_peri_pmc60.u32 = gopPMCAllReg->PERI_PMC60.u32;
    o_peri_pmc60.bits.pmu_reg4 = upmu_reg4;
    gopPMCAllReg->PERI_PMC60.u32 = o_peri_pmc60.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC60.u32));

    return 1;
}
int iGetPERI_PMC60pmu_reg4(unsigned int *upmu_reg4)
{
    *upmu_reg4 = gopPMCAllReg->PERI_PMC60.bits.pmu_reg4;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC60pmu_reg5
//  Description : Set the value of the member PERI_PMC60.pmu_reg5
//  Input       : unsigned int upmu_reg5: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC60pmu_reg5(unsigned int upmu_reg5)
{
    U_PERI_PMC60 o_peri_pmc60;
    o_peri_pmc60.u32 = gopPMCAllReg->PERI_PMC60.u32;
    o_peri_pmc60.bits.pmu_reg5 = upmu_reg5;
    gopPMCAllReg->PERI_PMC60.u32 = o_peri_pmc60.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC60.u32));

    return 1;
}

int iGetPERI_PMC60pmu_reg5(unsigned int *upmu_reg5)
{
    *upmu_reg5 = gopPMCAllReg->PERI_PMC60.bits.pmu_reg5;
    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC60pmu_reg6
//  Description : Set the value of the member PERI_PMC60.pmu_reg6
//  Input       : unsigned int upmu_reg6: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC60pmu_reg6(unsigned int upmu_reg6)
{
    U_PERI_PMC60 o_peri_pmc60;
    o_peri_pmc60.u32 = gopPMCAllReg->PERI_PMC60.u32;
    o_peri_pmc60.bits.pmu_reg6 = upmu_reg6;
    gopPMCAllReg->PERI_PMC60.u32 = o_peri_pmc60.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC60.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC60pmu_reg7
//  Description : Set the value of the member PERI_PMC60.pmu_reg7
//  Input       : unsigned int upmu_reg7: 8 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC60pmu_reg7(unsigned int upmu_reg7)
{
    U_PERI_PMC60 o_peri_pmc60;
    o_peri_pmc60.u32 = gopPMCAllReg->PERI_PMC60.u32;
    o_peri_pmc60.bits.pmu_reg7 = upmu_reg7;
    gopPMCAllReg->PERI_PMC60.u32 = o_peri_pmc60.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC60.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC62pmc_i2c_lcnt
//  Description : Set the value of the member PERI_PMC62.pmc_i2c_lcnt
//  Input       : unsigned int upmc_i2c_lcnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC62pmc_i2c_lcnt(unsigned int upmc_i2c_lcnt)
{
    U_PERI_PMC62 o_peri_pmc62;
    o_peri_pmc62.u32 = gopPMCAllReg->PERI_PMC62.u32;
    o_peri_pmc62.bits.pmc_i2c_lcnt = upmc_i2c_lcnt;
    gopPMCAllReg->PERI_PMC62.u32 = o_peri_pmc62.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC62.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC62pmc_i2c_hcnt
//  Description : Set the value of the member PERI_PMC62.pmc_i2c_hcnt
//  Input       : unsigned int upmc_i2c_hcnt: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC62pmc_i2c_hcnt(unsigned int upmc_i2c_hcnt)
{
    U_PERI_PMC62 o_peri_pmc62;
    o_peri_pmc62.u32 = gopPMCAllReg->PERI_PMC62.u32;
    o_peri_pmc62.bits.pmc_i2c_hcnt = upmc_i2c_hcnt;
    gopPMCAllReg->PERI_PMC62.u32 = o_peri_pmc62.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC62.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg0_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg0_mux
//  Input       : unsigned int upmu_avs_reg0_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg0_mux(unsigned int upmu_avs_reg0_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg0_mux = upmu_avs_reg0_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg1_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg1_mux
//  Input       : unsigned int upmu_avs_reg1_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg1_mux(unsigned int upmu_avs_reg1_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg1_mux = upmu_avs_reg1_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg2_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg2_mux
//  Input       : unsigned int upmu_avs_reg2_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg2_mux(unsigned int upmu_avs_reg2_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg2_mux = upmu_avs_reg2_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg3_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg3_mux
//  Input       : unsigned int upmu_avs_reg3_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg3_mux(unsigned int upmu_avs_reg3_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg3_mux = upmu_avs_reg3_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg4_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg4_mux
//  Input       : unsigned int upmu_avs_reg4_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg4_mux(unsigned int upmu_avs_reg4_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg4_mux = upmu_avs_reg4_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg5_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg5_mux
//  Input       : unsigned int upmu_avs_reg5_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg5_mux(unsigned int upmu_avs_reg5_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg5_mux = upmu_avs_reg5_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg6_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg6_mux
//  Input       : unsigned int upmu_avs_reg6_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg6_mux(unsigned int upmu_avs_reg6_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg6_mux = upmu_avs_reg6_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg7_mux
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg7_mux
//  Input       : unsigned int upmu_avs_reg7_mux: 2 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg7_mux(unsigned int upmu_avs_reg7_mux)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg7_mux = upmu_avs_reg7_mux;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg0_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg0_en
//  Input       : unsigned int upmu_avs_reg0_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg0_en(unsigned int upmu_avs_reg0_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg0_en = upmu_avs_reg0_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg1_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg1_en
//  Input       : unsigned int upmu_avs_reg1_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg1_en(unsigned int upmu_avs_reg1_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg1_en = upmu_avs_reg1_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg2_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg2_en
//  Input       : unsigned int upmu_avs_reg2_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg2_en(unsigned int upmu_avs_reg2_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg2_en = upmu_avs_reg2_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg3_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg3_en
//  Input       : unsigned int upmu_avs_reg3_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg3_en(unsigned int upmu_avs_reg3_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg3_en = upmu_avs_reg3_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg4_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg4_en
//  Input       : unsigned int upmu_avs_reg4_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg4_en(unsigned int upmu_avs_reg4_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg4_en = upmu_avs_reg4_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg5_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg5_en
//  Input       : unsigned int upmu_avs_reg5_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg5_en(unsigned int upmu_avs_reg5_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg5_en = upmu_avs_reg5_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg6_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg6_en
//  Input       : unsigned int upmu_avs_reg6_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg6_en(unsigned int upmu_avs_reg6_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg6_en = upmu_avs_reg6_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC63pmu_avs_reg7_en
//  Description : Set the value of the member PERI_PMC63.pmu_avs_reg7_en
//  Input       : unsigned int upmu_avs_reg7_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC63pmu_avs_reg7_en(unsigned int upmu_avs_reg7_en)
{
    U_PERI_PMC63 o_peri_pmc63;
    o_peri_pmc63.u32 = gopPMCAllReg->PERI_PMC63.u32;
    o_peri_pmc63.bits.pmu_avs_reg7_en = upmu_avs_reg7_en;
    gopPMCAllReg->PERI_PMC63.u32 = o_peri_pmc63.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC63.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_ts_monitor_period
//  Description : Set the value of the member PERI_PMC64.core_ts_monitor_period
//  Input       : unsigned int ucore_ts_monitor_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_ts_monitor_period(unsigned int ucore_ts_monitor_period)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_ts_monitor_period = ucore_ts_monitor_period;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_ts_monitor_en
//  Description : Set the value of the member PERI_PMC64.core_ts_monitor_en
//  Input       : unsigned int ucore_ts_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_ts_monitor_en(unsigned int ucore_ts_monitor_en)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_ts_monitor_en = ucore_ts_monitor_en;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_ts_en_must_inc
//  Description : Set the value of the member PERI_PMC64.core_ts_en_must_inc
//  Input       : unsigned int ucore_ts_en_must_inc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_ts_en_must_inc(unsigned int ucore_ts_en_must_inc)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_ts_en_must_inc = ucore_ts_en_must_inc;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_avs_ctrl_sel
//  Description : Set the value of the member PERI_PMC64.core_avs_ctrl_sel
//  Input       : unsigned int ucore_avs_ctrl_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_avs_ctrl_sel(unsigned int ucore_avs_ctrl_sel)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_avs_ctrl_sel = ucore_avs_ctrl_sel;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_avs_ctrl_mux
//  Description : Set the value of the member PERI_PMC64.core_avs_ctrl_mux
//  Input       : unsigned int ucore_avs_ctrl_mux: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_avs_ctrl_mux(unsigned int ucore_avs_ctrl_mux)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_avs_ctrl_mux = ucore_avs_ctrl_mux;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC64core_ts_inc_case_sel
//  Description : Set the value of the member PERI_PMC64.core_ts_inc_case_sel
//  Input       : unsigned int ucore_ts_inc_case_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC64core_ts_inc_case_sel(unsigned int ucore_ts_inc_case_sel)
{
    U_PERI_PMC64 o_peri_pmc64;
    o_peri_pmc64.u32 = gopPMCAllReg->PERI_PMC64.u32;
    o_peri_pmc64.bits.core_ts_inc_case_sel = ucore_ts_inc_case_sel;
    gopPMCAllReg->PERI_PMC64.u32 = o_peri_pmc64.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC64.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_ts_monitor_period
//  Description : Set the value of the member PERI_PMC65.cpu_ts_monitor_period
//  Input       : unsigned int ucpu_ts_monitor_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_ts_monitor_period(unsigned int ucpu_ts_monitor_period)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_ts_monitor_period = ucpu_ts_monitor_period;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_ts_monitor_en
//  Description : Set the value of the member PERI_PMC65.cpu_ts_monitor_en
//  Input       : unsigned int ucpu_ts_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_ts_monitor_en(unsigned int ucpu_ts_monitor_en)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_ts_monitor_en = ucpu_ts_monitor_en;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_ts_en_must_inc
//  Description : Set the value of the member PERI_PMC65.cpu_ts_en_must_inc
//  Input       : unsigned int ucpu_ts_en_must_inc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_ts_en_must_inc(unsigned int ucpu_ts_en_must_inc)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_ts_en_must_inc = ucpu_ts_en_must_inc;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_avs_ctrl_sel
//  Description : Set the value of the member PERI_PMC65.cpu_avs_ctrl_sel
//  Input       : unsigned int ucpu_avs_ctrl_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_avs_ctrl_sel(unsigned int ucpu_avs_ctrl_sel)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_avs_ctrl_sel = ucpu_avs_ctrl_sel;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_avs_ctrl_mux
//  Description : Set the value of the member PERI_PMC65.cpu_avs_ctrl_mux
//  Input       : unsigned int ucpu_avs_ctrl_mux: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_avs_ctrl_mux(unsigned int ucpu_avs_ctrl_mux)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_avs_ctrl_mux = ucpu_avs_ctrl_mux;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC65cpu_ts_inc_case_sel
//  Description : Set the value of the member PERI_PMC65.cpu_ts_inc_case_sel
//  Input       : unsigned int ucpu_ts_inc_case_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC65cpu_ts_inc_case_sel(unsigned int ucpu_ts_inc_case_sel)
{
    U_PERI_PMC65 o_peri_pmc65;
    o_peri_pmc65.u32 = gopPMCAllReg->PERI_PMC65.u32;
    o_peri_pmc65.bits.cpu_ts_inc_case_sel = ucpu_ts_inc_case_sel;
    gopPMCAllReg->PERI_PMC65.u32 = o_peri_pmc65.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC65.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_ts_monitor_period
//  Description : Set the value of the member PERI_PMC66.ddr_ts_monitor_period
//  Input       : unsigned int uddr_ts_monitor_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_ts_monitor_period(unsigned int uddr_ts_monitor_period)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_ts_monitor_period = uddr_ts_monitor_period;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_ts_monitor_en
//  Description : Set the value of the member PERI_PMC66.ddr_ts_monitor_en
//  Input       : unsigned int uddr_ts_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_ts_monitor_en(unsigned int uddr_ts_monitor_en)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_ts_monitor_en = uddr_ts_monitor_en;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_ts_en_must_inc
//  Description : Set the value of the member PERI_PMC66.ddr_ts_en_must_inc
//  Input       : unsigned int uddr_ts_en_must_inc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_ts_en_must_inc(unsigned int uddr_ts_en_must_inc)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_ts_en_must_inc = uddr_ts_en_must_inc;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_avs_ctrl_sel
//  Description : Set the value of the member PERI_PMC66.ddr_avs_ctrl_sel
//  Input       : unsigned int uddr_avs_ctrl_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_avs_ctrl_sel(unsigned int uddr_avs_ctrl_sel)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_avs_ctrl_sel = uddr_avs_ctrl_sel;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_avs_ctrl_mux
//  Description : Set the value of the member PERI_PMC66.ddr_avs_ctrl_mux
//  Input       : unsigned int uddr_avs_ctrl_mux: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_avs_ctrl_mux(unsigned int uddr_avs_ctrl_mux)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_avs_ctrl_mux = uddr_avs_ctrl_mux;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC66ddr_ts_inc_case_sel
//  Description : Set the value of the member PERI_PMC66.ddr_ts_inc_case_sel
//  Input       : unsigned int uddr_ts_inc_case_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC66ddr_ts_inc_case_sel(unsigned int uddr_ts_inc_case_sel)
{
    U_PERI_PMC66 o_peri_pmc66;
    o_peri_pmc66.u32 = gopPMCAllReg->PERI_PMC66.u32;
    o_peri_pmc66.bits.ddr_ts_inc_case_sel = uddr_ts_inc_case_sel;
    gopPMCAllReg->PERI_PMC66.u32 = o_peri_pmc66.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC66.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_ts_monitor_period
//  Description : Set the value of the member PERI_PMC67.mda_ts_monitor_period
//  Input       : unsigned int umda_ts_monitor_period: 16 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_ts_monitor_period(unsigned int umda_ts_monitor_period)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_ts_monitor_period = umda_ts_monitor_period;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_ts_monitor_en
//  Description : Set the value of the member PERI_PMC67.mda_ts_monitor_en
//  Input       : unsigned int umda_ts_monitor_en: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_ts_monitor_en(unsigned int umda_ts_monitor_en)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_ts_monitor_en = umda_ts_monitor_en;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_ts_en_must_inc
//  Description : Set the value of the member PERI_PMC67.mda_ts_en_must_inc
//  Input       : unsigned int umda_ts_en_must_inc: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_ts_en_must_inc(unsigned int umda_ts_en_must_inc)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_ts_en_must_inc = umda_ts_en_must_inc;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_avs_ctrl_sel
//  Description : Set the value of the member PERI_PMC67.mda_avs_ctrl_sel
//  Input       : unsigned int umda_avs_ctrl_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_avs_ctrl_sel(unsigned int umda_avs_ctrl_sel)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_avs_ctrl_sel = umda_avs_ctrl_sel;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_avs_ctrl_mux
//  Description : Set the value of the member PERI_PMC67.mda_avs_ctrl_mux
//  Input       : unsigned int umda_avs_ctrl_mux: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_avs_ctrl_mux(unsigned int umda_avs_ctrl_mux)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_avs_ctrl_mux = umda_avs_ctrl_mux;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_avs_hpm_sel
//  Description : Set the value of the member PERI_PMC67.mda_avs_hpm_sel
//  Input       : unsigned int umda_avs_hpm_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_avs_hpm_sel(unsigned int umda_avs_hpm_sel)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_avs_hpm_sel = umda_avs_hpm_sel;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_avs_ts_sel
//  Description : Set the value of the member PERI_PMC67.mda_avs_ts_sel
//  Input       : unsigned int umda_avs_ts_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_avs_ts_sel(unsigned int umda_avs_ts_sel)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_avs_ts_sel = umda_avs_ts_sel;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

//******************************************************************************
//  Function    : iSetPERI_PMC67mda_ts_inc_case_sel
//  Description : Set the value of the member PERI_PMC67.mda_ts_inc_case_sel
//  Input       : unsigned int umda_ts_inc_case_sel: 1 bits
//  Return      : int: 0-Error, 1-Success
//******************************************************************************
int iSetPERI_PMC67mda_ts_inc_case_sel(unsigned int umda_ts_inc_case_sel)
{
    U_PERI_PMC67 o_peri_pmc67;
    o_peri_pmc67.u32 = gopPMCAllReg->PERI_PMC67.u32;
    o_peri_pmc67.bits.mda_ts_inc_case_sel = umda_ts_inc_case_sel;
    gopPMCAllReg->PERI_PMC67.u32 = o_peri_pmc67.u32;
    RTL_Verify_RegWrite(PMC_BASE_ADDR, (unsigned int *)&(gopPMCAllReg->PERI_PMC67.u32));

    return 1;
}

