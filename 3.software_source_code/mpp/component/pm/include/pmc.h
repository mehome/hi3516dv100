//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  pmc.h
// Author        :  xxx
// Version       :  1.0 
// Date          :  2014-06-19
// Description   :  Define all registers/tables for xxx
// Others        :  Generated automatically by nManager V4.0 
// History       :  xxx 2014-06-19 Create file
//******************************************************************************

#ifndef __PMC_H__
#define __PMC_H__

/* Define the union U_PERI_PMC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_pwm_period       : 16  ; /* [15..0]  */
        unsigned int    core_pwm_duty         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC0;

/* Define the union U_PERI_PMC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_pwm_period        : 16  ; /* [15..0]  */
        unsigned int    cpu_pwm_duty          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC1;

/* Define the union U_PERI_PMC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_pwm_period        : 16  ; /* [15..0]  */
        unsigned int    ddr_pwm_duty          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC2;

/* Define the union U_PERI_PMC3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_pwm_period        : 16  ; /* [15..0]  */
        unsigned int    mda_pwm_duty          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC3;

/* Define the union U_PERI_PMC4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_pwm_enable       : 1   ; /* [0]  */
        unsigned int    core_pwm_inv          : 1   ; /* [1]  */
        unsigned int    cpu_pwm_enable        : 1   ; /* [2]  */
        unsigned int    cpu_pwm_inv           : 1   ; /* [3]  */
        unsigned int    ddr_pwm_enable        : 1   ; /* [4]  */
        unsigned int    ddr_pwm_inv           : 1   ; /* [5]  */
        unsigned int    mda_pwm_enable        : 1   ; /* [6]  */
        unsigned int    mda_pwm_inv           : 1   ; /* [7]  */
        unsigned int    pwm0_reuse_cfg        : 2   ; /* [9..8]  */
        unsigned int    pwm1_reuse_cfg        : 2   ; /* [11..10]  */
        unsigned int    pwm2_reuse_cfg        : 2   ; /* [13..12]  */
        unsigned int    pwm3_reuse_cfg        : 2   ; /* [15..14]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC4;

/* Define the union U_PERI_PMC5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_fsm_en       : 1   ; /* [0]  */
        unsigned int    core_avs_hpm_fsm_calc_mode : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    core_avs_fsm_dec_pwm_step : 8   ; /* [23..16]  */
        unsigned int    core_avs_fsm_inc_pwm_step : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC5;

/* Define the union U_PERI_PMC6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_hpm_fsm_en        : 1   ; /* [0]  */
        unsigned int    cpu_avs_hpm_fsm_calc_mode : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    cpu_avs_fsm_dec_pwm_step : 8   ; /* [23..16]  */
        unsigned int    cpu_avs_fsm_inc_pwm_step : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC6;

/* Define the union U_PERI_PMC7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_hpm_fsm_en        : 1   ; /* [0]  */
        unsigned int    ddr_avs_hpm_fsm_calc_mode : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    ddr_avs_fsm_dec_pwm_step : 8   ; /* [23..16]  */
        unsigned int    ddr_avs_fsm_inc_pwm_step : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC7;

/* Define the union U_PERI_PMC8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_hpm_fsm_en        : 1   ; /* [0]  */
        unsigned int    mda_avs_hpm_fsm_calc_mode : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 13  ; /* [15..3]  */
        unsigned int    mda_avs_fsm_dec_pwm_step : 8   ; /* [23..16]  */
        unsigned int    mda_avs_fsm_inc_pwm_step : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC8;

/* Define the union U_PERI_PMC9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_avs_state_machine : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    cpu_avs_state_machine : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    ddr_avs_state_machine : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    mda_avs_state_machine : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC9;

/* Define the union U_PERI_PMC10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_div          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    core_hpm_shift        : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    core_hpm_offset       : 10  ; /* [21..12]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    core_hpm_en           : 1   ; /* [24]  */
        unsigned int    core_hpm_bypass       : 1   ; /* [25]  */
        unsigned int    core_hpm_monitor_en   : 1   ; /* [26]  */
        unsigned int    core_hpm_srst_req     : 1   ; /* [27]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC10;

/* Define the union U_PERI_PMC11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_pc_record0   : 10  ; /* [9..0]  */
        unsigned int    core_hpm_pc_valid     : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    core_hpm_pc_record1   : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    core_hpm_low_warning  : 1   ; /* [24]  */
        unsigned int    core_hpm_up_warning   : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC11;

/* Define the union U_PERI_PMC12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_pc_record2   : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    core_hpm_pc_record3   : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    core_hpm_rcc          : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC12;

/* Define the union U_PERI_PMC13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_uplimit      : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    core_hpm_lowlimit     : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    core_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC13;

/* Define the union U_PERI_PMC14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_hpm_div           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    cpu_hpm_shift         : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    cpu_hpm_offset        : 10  ; /* [21..12]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    cpu_hpm_en            : 1   ; /* [24]  */
        unsigned int    cpu_hpm_bypass        : 1   ; /* [25]  */
        unsigned int    cpu_hpm_monitor_en    : 1   ; /* [26]  */
        unsigned int    cpu_hpm_srst_req      : 1   ; /* [27]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC14;

/* Define the union U_PERI_PMC15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_hpm_pc_record0    : 10  ; /* [9..0]  */
        unsigned int    cpu_hpm_pc_valid      : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    cpu_hpm_pc_record1    : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    cpu_hpm_low_warning   : 1   ; /* [24]  */
        unsigned int    cpu_hpm_up_warning    : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC15;

/* Define the union U_PERI_PMC16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_hpm_pc_record2    : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    cpu_hpm_pc_record3    : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    cpu_hpm_rcc           : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC16;

/* Define the union U_PERI_PMC17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_hpm_uplimit       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    cpu_hpm_lowlimit      : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    cpu_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC17;

/* Define the union U_PERI_PMC18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_hpm_div           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    ddr_hpm_shift         : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    ddr_hpm_offset        : 10  ; /* [21..12]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    ddr_hpm_en            : 1   ; /* [24]  */
        unsigned int    ddr_hpm_bypass        : 1   ; /* [25]  */
        unsigned int    ddr_hpm_monitor_en    : 1   ; /* [26]  */
        unsigned int    ddr_hpm_srst_req      : 1   ; /* [27]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC18;

/* Define the union U_PERI_PMC19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_hpm_pc_record0    : 10  ; /* [9..0]  */
        unsigned int    ddr_hpm_pc_valid      : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    ddr_hpm_pc_record1    : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    ddr_hpm_low_warning   : 1   ; /* [24]  */
        unsigned int    ddr_hpm_up_warning    : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC19;

/* Define the union U_PERI_PMC20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_hpm_pc_record2    : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    ddr_hpm_pc_record3    : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    ddr_hpm_rcc           : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC20;

/* Define the union U_PERI_PMC21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_hpm_uplimit       : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    ddr_hpm_lowlimit      : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    ddr_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC21;

/* Define the union U_PERI_PMC22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_hpm_div       : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    mda_top_hpm_shift     : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    mda_top_hpm_offset    : 10  ; /* [21..12]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    mda_top_hpm_en        : 1   ; /* [24]  */
        unsigned int    mda_top_hpm_bypass    : 1   ; /* [25]  */
        unsigned int    mda_top_hpm_monitor_en : 1   ; /* [26]  */
        unsigned int    mda_top_hpm_srst_req  : 1   ; /* [27]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC22;

/* Define the union U_PERI_PMC23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_hpm_pc_record0 : 10  ; /* [9..0]  */
        unsigned int    mda_top_hpm_pc_valid  : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    mda_top_hpm_pc_record1 : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    mda_top_hpm_low_warning : 1   ; /* [24]  */
        unsigned int    mda_top_hpm_up_warning : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC23;

/* Define the union U_PERI_PMC24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_hpm_pc_record2 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    mda_top_hpm_pc_record3 : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    mda_top_hpm_rcc       : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC24;

/* Define the union U_PERI_PMC25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_hpm_uplimit   : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    mda_top_hpm_lowlimit  : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    mda_top_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC25;

/* Define the union U_PERI_PMC26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_hpm_div          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    vedu_hpm_shift        : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    vedu_hpm_offset       : 10  ; /* [21..12]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    vedu_hpm_en           : 1   ; /* [24]  */
        unsigned int    vedu_hpm_bypass       : 1   ; /* [25]  */
        unsigned int    vedu_hpm_monitor_en   : 1   ; /* [26]  */
        unsigned int    vedu_hpm_srst_req     : 1   ; /* [27]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC26;

/* Define the union U_PERI_PMC27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_hpm_pc_record0   : 10  ; /* [9..0]  */
        unsigned int    vedu_hpm_pc_valid     : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    vedu_hpm_pc_record1   : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    vedu_hpm_low_warning  : 1   ; /* [24]  */
        unsigned int    vedu_hpm_up_warning   : 1   ; /* [25]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC27;

/* Define the union U_PERI_PMC28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_hpm_pc_record2   : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    vedu_hpm_pc_record3   : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    vedu_hpm_rcc          : 5   ; /* [28..24]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC28;

/* Define the union U_PERI_PMC29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_hpm_uplimit      : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    vedu_hpm_lowlimit     : 10  ; /* [21..12]  */
        unsigned int    reserved_1            : 2   ; /* [23..22]  */
        unsigned int    vedu_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC29;

/* Define the union U_PERI_PMC30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_hpm_monitor_period : 8   ; /* [7..0]  */
        unsigned int    mda_top_hpm_monitor_period : 8   ; /* [15..8]  */
        unsigned int    ddr_hpm_monitor_period : 8   ; /* [23..16]  */
        unsigned int    cpu_hpm_monitor_period : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC30;

/* Define the union U_PERI_PMC31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hpm_monitor_period : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC31;

/* Define the union U_PERI_PMC32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_sel            : 1   ; /* [0]  */
        unsigned int    cpu_ts_dly_adjust     : 4   ; /* [4..1]  */
        unsigned int    cpu_ts_step           : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    cpu_ts_en             : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC32;

/* Define the union U_PERI_PMC33 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_sel            : 1   ; /* [0]  */
        unsigned int    ddr_ts_dly_adjust     : 4   ; /* [4..1]  */
        unsigned int    ddr_ts_step           : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    ddr_ts_en             : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC33;

/* Define the union U_PERI_PMC34 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_sel           : 1   ; /* [0]  */
        unsigned int    core_ts_dly_adjust    : 4   ; /* [4..1]  */
        unsigned int    core_ts_step          : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    core_ts_en            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC34;

/* Define the union U_PERI_PMC35 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_ts_sel        : 1   ; /* [0]  */
        unsigned int    mda_top_ts_dly_adjust : 4   ; /* [4..1]  */
        unsigned int    mda_top_ts_step       : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    mda_top_ts_en         : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC35;

/* Define the union U_PERI_PMC36 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_ts_sel           : 1   ; /* [0]  */
        unsigned int    vedu_ts_dly_adjust    : 4   ; /* [4..1]  */
        unsigned int    vedu_ts_step          : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    vedu_ts_en            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC36;

/* Define the union U_PERI_PMC37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_stat           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    cpu_ts_record1        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC37;

/* Define the union U_PERI_PMC38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_record2        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    cpu_ts_record3        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC38;

/* Define the union U_PERI_PMC39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_record4        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    cpu_ts_record5        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC39;

/* Define the union U_PERI_PMC40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_record6        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    cpu_ts_record7        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC40;

/* Define the union U_PERI_PMC41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_stat           : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ddr_ts_record1        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC41;

/* Define the union U_PERI_PMC42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_record2        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ddr_ts_record3        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC42;

/* Define the union U_PERI_PMC43 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_record4        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ddr_ts_record5        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC43;

/* Define the union U_PERI_PMC44 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_record6        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ddr_ts_record7        : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC44;

/* Define the union U_PERI_PMC45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_stat          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    core_ts_record1       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC45;

/* Define the union U_PERI_PMC46 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_record2       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    core_ts_record3       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC46;

/* Define the union U_PERI_PMC47 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_record4       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    core_ts_record5       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC47;

/* Define the union U_PERI_PMC48 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_record6       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    core_ts_record7       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC48;

/* Define the union U_PERI_PMC49 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_ts_stat       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    mda_top_ts_record1    : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC49;

/* Define the union U_PERI_PMC50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_ts_record2    : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    mda_top_ts_record3    : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC50;

/* Define the union U_PERI_PMC51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_ts_record4    : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    mda_top_ts_record5    : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC51;

/* Define the union U_PERI_PMC52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_top_ts_record6    : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    mda_top_ts_record7    : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC52;

/* Define the union U_PERI_PMC53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_ts_stat          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    vedu_ts_record1       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC53;

/* Define the union U_PERI_PMC54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_ts_record2       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    vedu_ts_record3       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC54;

/* Define the union U_PERI_PMC55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_ts_record4       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    vedu_ts_record5       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC55;

/* Define the union U_PERI_PMC56 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vedu_ts_record6       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    vedu_ts_record7       : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC56;

/* Define the union U_PERI_PMC57 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PERI_PMC57;
/* Define the union U_PERI_PMC58 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmu_addr              : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    pmu_reg_rd_all        : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    pmu_reg0_wt_req       : 1   ; /* [12]  */
        unsigned int    pmu_reg1_wt_req       : 1   ; /* [13]  */
        unsigned int    pmu_reg2_wt_req       : 1   ; /* [14]  */
        unsigned int    pmu_reg3_wt_req       : 1   ; /* [15]  */
        unsigned int    pmu_reg4_wt_req       : 1   ; /* [16]  */
        unsigned int    pmu_reg5_wt_req       : 1   ; /* [17]  */
        unsigned int    pmu_reg6_wt_req       : 1   ; /* [18]  */
        unsigned int    pmu_reg7_wt_req       : 1   ; /* [19]  */
        unsigned int    reserved_2            : 10  ; /* [29..20]  */
        unsigned int    i2c_int_clear         : 1   ; /* [30]  */
        unsigned int    pmc_i2c_enable        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC58;

/* Define the union U_PERI_PMC59 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmu_reg0              : 8   ; /* [7..0]  */
        unsigned int    pmu_reg1              : 8   ; /* [15..8]  */
        unsigned int    pmu_reg2              : 8   ; /* [23..16]  */
        unsigned int    pmu_reg3              : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC59;

/* Define the union U_PERI_PMC60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmu_reg4              : 8   ; /* [7..0]  */
        unsigned int    pmu_reg5              : 8   ; /* [15..8]  */
        unsigned int    pmu_reg6              : 8   ; /* [23..16]  */
        unsigned int    pmu_reg7              : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC60;

/* Define the union U_PERI_PMC61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i2c_stop_det          : 1   ; /* [0]  */
        unsigned int    i2c_start_det         : 1   ; /* [1]  */
        unsigned int    i2c_arb_lost          : 1   ; /* [2]  */
        unsigned int    i2c_mst_tx_abrt       : 1   ; /* [3]  */
        unsigned int    i2c_abrt_data_nack    : 1   ; /* [4]  */
        unsigned int    i2c_abrt_7addr_nack   : 1   ; /* [5]  */
        unsigned int    i2c_busy              : 1   ; /* [6]  */
        unsigned int    i2c_mst_active        : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC61;

/* Define the union U_PERI_PMC62 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmc_i2c_lcnt          : 16  ; /* [15..0]  */
        unsigned int    pmc_i2c_hcnt          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC62;

/* Define the union U_PERI_PMC63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmu_avs_reg0_mux      : 2   ; /* [1..0]  */
        unsigned int    pmu_avs_reg1_mux      : 2   ; /* [3..2]  */
        unsigned int    pmu_avs_reg2_mux      : 2   ; /* [5..4]  */
        unsigned int    pmu_avs_reg3_mux      : 2   ; /* [7..6]  */
        unsigned int    pmu_avs_reg4_mux      : 2   ; /* [9..8]  */
        unsigned int    pmu_avs_reg5_mux      : 2   ; /* [11..10]  */
        unsigned int    pmu_avs_reg6_mux      : 2   ; /* [13..12]  */
        unsigned int    pmu_avs_reg7_mux      : 2   ; /* [15..14]  */
        unsigned int    pmu_avs_reg0_en       : 1   ; /* [16]  */
        unsigned int    pmu_avs_reg1_en       : 1   ; /* [17]  */
        unsigned int    pmu_avs_reg2_en       : 1   ; /* [18]  */
        unsigned int    pmu_avs_reg3_en       : 1   ; /* [19]  */
        unsigned int    pmu_avs_reg4_en       : 1   ; /* [20]  */
        unsigned int    pmu_avs_reg5_en       : 1   ; /* [21]  */
        unsigned int    pmu_avs_reg6_en       : 1   ; /* [22]  */
        unsigned int    pmu_avs_reg7_en       : 1   ; /* [23]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC63;

/* Define the union U_PERI_PMC64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_ts_monitor_period : 16  ; /* [15..0]  */
        unsigned int    core_ts_monitor_en    : 1   ; /* [16]  */
        unsigned int    core_ts_en_must_inc   : 1   ; /* [17]  */
        unsigned int    core_avs_ctrl_sel     : 1   ; /* [18]  */
        unsigned int    core_avs_ctrl_mux     : 1   ; /* [19]  */
        unsigned int    reserved_0            : 2   ; /* [21..20]  */
        unsigned int    core_ts_inc_case_sel  : 1   ; /* [22]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC64;

/* Define the union U_PERI_PMC65 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_ts_monitor_period : 16  ; /* [15..0]  */
        unsigned int    cpu_ts_monitor_en     : 1   ; /* [16]  */
        unsigned int    cpu_ts_en_must_inc    : 1   ; /* [17]  */
        unsigned int    cpu_avs_ctrl_sel      : 1   ; /* [18]  */
        unsigned int    cpu_avs_ctrl_mux      : 1   ; /* [19]  */
        unsigned int    reserved_0            : 2   ; /* [21..20]  */
        unsigned int    cpu_ts_inc_case_sel   : 1   ; /* [22]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC65;

/* Define the union U_PERI_PMC66 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_ts_monitor_period : 16  ; /* [15..0]  */
        unsigned int    ddr_ts_monitor_en     : 1   ; /* [16]  */
        unsigned int    ddr_ts_en_must_inc    : 1   ; /* [17]  */
        unsigned int    ddr_avs_ctrl_sel      : 1   ; /* [18]  */
        unsigned int    ddr_avs_ctrl_mux      : 1   ; /* [19]  */
        unsigned int    reserved_0            : 2   ; /* [21..20]  */
        unsigned int    ddr_ts_inc_case_sel   : 1   ; /* [22]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC66;

/* Define the union U_PERI_PMC67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mda_ts_monitor_period : 16  ; /* [15..0]  */
        unsigned int    mda_ts_monitor_en     : 1   ; /* [16]  */
        unsigned int    mda_ts_en_must_inc    : 1   ; /* [17]  */
        unsigned int    mda_avs_ctrl_sel      : 1   ; /* [18]  */
        unsigned int    mda_avs_ctrl_mux      : 1   ; /* [19]  */
        unsigned int    mda_avs_hpm_sel       : 1   ; /* [20]  */
        unsigned int    mda_avs_ts_sel        : 1   ; /* [21]  */
        unsigned int    mda_ts_inc_case_sel   : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_PMC67;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_PERI_PMC0            PERI_PMC0                         ; /* 0x0 */
    volatile U_PERI_PMC1            PERI_PMC1                         ; /* 0x4 */
    volatile U_PERI_PMC2            PERI_PMC2                         ; /* 0x8 */
    volatile U_PERI_PMC3            PERI_PMC3                         ; /* 0xc */
    volatile U_PERI_PMC4            PERI_PMC4                         ; /* 0x10 */
    volatile U_PERI_PMC5            PERI_PMC5                         ; /* 0x14 */
    volatile U_PERI_PMC6            PERI_PMC6                         ; /* 0x18 */
    volatile U_PERI_PMC7            PERI_PMC7                         ; /* 0x1c */
    volatile U_PERI_PMC8            PERI_PMC8                         ; /* 0x20 */
    volatile U_PERI_PMC9            PERI_PMC9                         ; /* 0x24 */
    volatile U_PERI_PMC10           PERI_PMC10                        ; /* 0x28 */
    volatile U_PERI_PMC11           PERI_PMC11                        ; /* 0x2c */
    volatile U_PERI_PMC12           PERI_PMC12                        ; /* 0x30 */
    volatile U_PERI_PMC13           PERI_PMC13                        ; /* 0x34 */
    volatile U_PERI_PMC14           PERI_PMC14                        ; /* 0x38 */
    volatile U_PERI_PMC15           PERI_PMC15                        ; /* 0x3c */
    volatile U_PERI_PMC16           PERI_PMC16                        ; /* 0x40 */
    volatile U_PERI_PMC17           PERI_PMC17                        ; /* 0x44 */
    volatile U_PERI_PMC18           PERI_PMC18                        ; /* 0x48 */
    volatile U_PERI_PMC19           PERI_PMC19                        ; /* 0x4c */
    volatile U_PERI_PMC20           PERI_PMC20                        ; /* 0x50 */
    volatile U_PERI_PMC21           PERI_PMC21                        ; /* 0x54 */
    volatile U_PERI_PMC22           PERI_PMC22                        ; /* 0x58 */
    volatile U_PERI_PMC23           PERI_PMC23                        ; /* 0x5c */
    volatile U_PERI_PMC24           PERI_PMC24                        ; /* 0x60 */
    volatile U_PERI_PMC25           PERI_PMC25                        ; /* 0x64 */
    volatile U_PERI_PMC26           PERI_PMC26                        ; /* 0x68 */
    volatile U_PERI_PMC27           PERI_PMC27                        ; /* 0x6c */
    volatile U_PERI_PMC28           PERI_PMC28                        ; /* 0x70 */
    volatile U_PERI_PMC29           PERI_PMC29                        ; /* 0x74 */
    volatile U_PERI_PMC30           PERI_PMC30                        ; /* 0x78 */
    volatile U_PERI_PMC31           PERI_PMC31                        ; /* 0x7c */
    volatile U_PERI_PMC32           PERI_PMC32                        ; /* 0x80 */
    volatile U_PERI_PMC33           PERI_PMC33                        ; /* 0x84 */
    volatile U_PERI_PMC34           PERI_PMC34                        ; /* 0x88 */
    volatile U_PERI_PMC35           PERI_PMC35                        ; /* 0x8c */
    volatile U_PERI_PMC36           PERI_PMC36                        ; /* 0x90 */
    volatile U_PERI_PMC37           PERI_PMC37                        ; /* 0x94 */
    volatile U_PERI_PMC38           PERI_PMC38                        ; /* 0x98 */
    volatile U_PERI_PMC39           PERI_PMC39                        ; /* 0x9c */
    volatile U_PERI_PMC40           PERI_PMC40                        ; /* 0xa0 */
    volatile U_PERI_PMC41           PERI_PMC41                        ; /* 0xa4 */
    volatile U_PERI_PMC42           PERI_PMC42                        ; /* 0xa8 */
    volatile U_PERI_PMC43           PERI_PMC43                        ; /* 0xac */
    volatile U_PERI_PMC44           PERI_PMC44                        ; /* 0xb0 */
    volatile U_PERI_PMC45           PERI_PMC45                        ; /* 0xb4 */
    volatile U_PERI_PMC46           PERI_PMC46                        ; /* 0xb8 */
    volatile U_PERI_PMC47           PERI_PMC47                        ; /* 0xbc */
    volatile U_PERI_PMC48           PERI_PMC48                        ; /* 0xc0 */
    volatile U_PERI_PMC49           PERI_PMC49                        ; /* 0xc4 */
    volatile U_PERI_PMC50           PERI_PMC50                        ; /* 0xc8 */
    volatile U_PERI_PMC51           PERI_PMC51                        ; /* 0xcc */
    volatile U_PERI_PMC52           PERI_PMC52                        ; /* 0xd0 */
    volatile U_PERI_PMC53           PERI_PMC53                        ; /* 0xd4 */
    volatile U_PERI_PMC54           PERI_PMC54                        ; /* 0xd8 */
    volatile U_PERI_PMC55           PERI_PMC55                        ; /* 0xdc */
    volatile U_PERI_PMC56           PERI_PMC56                        ; /* 0xe0 */
    volatile U_PERI_PMC57           PERI_PMC57                        ; /* 0xe4 */
    volatile U_PERI_PMC58           PERI_PMC58                        ; /* 0xe8 */
    volatile U_PERI_PMC59           PERI_PMC59                        ; /* 0xec */
    volatile U_PERI_PMC60           PERI_PMC60                        ; /* 0xf0 */
    volatile U_PERI_PMC61           PERI_PMC61                        ; /* 0xf4 */
    volatile U_PERI_PMC62           PERI_PMC62                        ; /* 0xf8 */
    volatile U_PERI_PMC63           PERI_PMC63                        ; /* 0xfc */
    volatile U_PERI_PMC64           PERI_PMC64                        ; /* 0x100 */
    volatile U_PERI_PMC65           PERI_PMC65                        ; /* 0x104 */
    volatile U_PERI_PMC66           PERI_PMC66                        ; /* 0x108 */
    volatile U_PERI_PMC67           PERI_PMC67                        ; /* 0x10c */
} S_PMC_REGS_TYPE;

/* Declare the struct pointor of the module PMC */
extern S_PMC_REGS_TYPE *gopPMCAllReg;


int iSetPERI_PMC0core_pwm_period(unsigned int ucore_pwm_period);
int iSetPERI_PMC0core_pwm_duty(unsigned int ucore_pwm_duty);
int iSetPERI_PMC1cpu_pwm_period(unsigned int ucpu_pwm_period);
int iSetPERI_PMC1cpu_pwm_duty(unsigned int ucpu_pwm_duty);
int iGetPERI_PMC1cpu_pwm_period(void);
int iGetPERI_PMC1cpu_pwm_duty(void);
int iSetPERI_PMC2ddr_pwm_period(unsigned int uddr_pwm_period);
int iSetPERI_PMC2ddr_pwm_duty(unsigned int uddr_pwm_duty);
int iSetPERI_PMC3mda_pwm_period(unsigned int umda_pwm_period);
int iSetPERI_PMC3mda_pwm_duty(unsigned int umda_pwm_duty);
int iGetPERI_PMC3mda_pwm_period(void);
int iGetPERI_PMC3mda_pwm_duty(void);
int iSetPERI_PMC4core_pwm_enable(unsigned int ucore_pwm_enable);
int iSetPERI_PMC4core_pwm_inv(unsigned int ucore_pwm_inv);
int iSetPERI_PMC4cpu_pwm_enable(unsigned int ucpu_pwm_enable);
int iGetPERI_PMC4cpu_pwm_enable(unsigned int *ucpu_pwm_enable);
int iSetPERI_PMC4cpu_pwm_inv(unsigned int ucpu_pwm_inv);
int iSetPERI_PMC4ddr_pwm_enable(unsigned int uddr_pwm_enable);
int iSetPERI_PMC4ddr_pwm_inv(unsigned int uddr_pwm_inv);
int iSetPERI_PMC4mda_pwm_enable(unsigned int umda_pwm_enable);
int iGetPERI_PMC4mda_pwm_enable(unsigned int *umda_pwm_enable);
int iSetPERI_PMC4mda_pwm_inv(unsigned int umda_pwm_inv);
int iSetPERI_PMC4pwm0_reuse_cfg(unsigned int upwm0_reuse_cfg);
int iSetPERI_PMC4pwm1_reuse_cfg(unsigned int upwm1_reuse_cfg);
int iSetPERI_PMC4pwm2_reuse_cfg(unsigned int upwm2_reuse_cfg);
int iSetPERI_PMC4pwm3_reuse_cfg(unsigned int upwm3_reuse_cfg);
int iSetPERI_PMC5core_hpm_fsm_en(unsigned int ucore_hpm_fsm_en);
int iSetPERI_PMC5core_avs_hpm_fsm_calc_mode(unsigned int ucore_avs_hpm_fsm_calc_mode);
int iSetPERI_PMC5core_avs_fsm_dec_pwm_step(unsigned int ucore_avs_fsm_dec_pwm_step);
int iSetPERI_PMC5core_avs_fsm_inc_pwm_step(unsigned int ucore_avs_fsm_inc_pwm_step);
int iSetPERI_PMC6cpu_hpm_fsm_en(unsigned int ucpu_hpm_fsm_en);
int iSetPERI_PMC6cpu_avs_hpm_fsm_calc_mode(unsigned int ucpu_avs_hpm_fsm_calc_mode);
int iSetPERI_PMC6cpu_avs_fsm_dec_pwm_step(unsigned int ucpu_avs_fsm_dec_pwm_step);
int iSetPERI_PMC6cpu_avs_fsm_inc_pwm_step(unsigned int ucpu_avs_fsm_inc_pwm_step);
int iSetPERI_PMC7ddr_hpm_fsm_en(unsigned int uddr_hpm_fsm_en);
int iSetPERI_PMC7ddr_avs_hpm_fsm_calc_mode(unsigned int uddr_avs_hpm_fsm_calc_mode);
int iSetPERI_PMC7ddr_avs_fsm_dec_pwm_step(unsigned int uddr_avs_fsm_dec_pwm_step);
int iSetPERI_PMC7ddr_avs_fsm_inc_pwm_step(unsigned int uddr_avs_fsm_inc_pwm_step);
int iSetPERI_PMC8mda_hpm_fsm_en(unsigned int umda_hpm_fsm_en);
int iSetPERI_PMC8mda_avs_hpm_fsm_calc_mode(unsigned int umda_avs_hpm_fsm_calc_mode);
int iSetPERI_PMC8mda_avs_fsm_dec_pwm_step(unsigned int umda_avs_fsm_dec_pwm_step);
int iSetPERI_PMC8mda_avs_fsm_inc_pwm_step(unsigned int umda_avs_fsm_inc_pwm_step);
int iSetPERI_PMC10core_hpm_div(unsigned int ucore_hpm_div);
int iSetPERI_PMC10core_hpm_shift(unsigned int ucore_hpm_shift);
int iSetPERI_PMC10core_hpm_offset(unsigned int ucore_hpm_offset);
int iSetPERI_PMC10core_hpm_en(unsigned int ucore_hpm_en);
int iSetPERI_PMC10core_hpm_bypass(unsigned int ucore_hpm_bypass);
int iSetPERI_PMC10core_hpm_monitor_en(unsigned int ucore_hpm_monitor_en);
int iSetPERI_PMC10core_hpm_srst_req(unsigned int ucore_hpm_srst_req);
int iSetPERI_PMC13core_hpm_uplimit(unsigned int ucore_hpm_uplimit);
int iSetPERI_PMC13core_hpm_lowlimit(unsigned int ucore_hpm_lowlimit);
int iSetPERI_PMC13core_hpm_monitor_period(unsigned int ucore_hpm_monitor_period);
int iSetPERI_PMC14cpu_hpm_div(unsigned int ucpu_hpm_div);
int iSetPERI_PMC14cpu_hpm_shift(unsigned int ucpu_hpm_shift);
int iSetPERI_PMC14cpu_hpm_offset(unsigned int ucpu_hpm_offset);
int iSetPERI_PMC14cpu_hpm_en(unsigned int ucpu_hpm_en);
int iSetPERI_PMC14cpu_hpm_bypass(unsigned int ucpu_hpm_bypass);
int iSetPERI_PMC14cpu_hpm_monitor_en(unsigned int ucpu_hpm_monitor_en);
int iSetPERI_PMC14cpu_hpm_srst_req(unsigned int ucpu_hpm_srst_req);
int iSetPERI_PMC17cpu_hpm_uplimit(unsigned int ucpu_hpm_uplimit);
int iSetPERI_PMC17cpu_hpm_lowlimit(unsigned int ucpu_hpm_lowlimit);
int iSetPERI_PMC17cpu_hpm_monitor_period(unsigned int ucpu_hpm_monitor_period);
int iSetPERI_PMC18ddr_hpm_div(unsigned int uddr_hpm_div);
int iSetPERI_PMC18ddr_hpm_shift(unsigned int uddr_hpm_shift);
int iSetPERI_PMC18ddr_hpm_offset(unsigned int uddr_hpm_offset);
int iSetPERI_PMC18ddr_hpm_en(unsigned int uddr_hpm_en);
int iSetPERI_PMC18ddr_hpm_bypass(unsigned int uddr_hpm_bypass);
int iSetPERI_PMC18ddr_hpm_monitor_en(unsigned int uddr_hpm_monitor_en);
int iSetPERI_PMC18ddr_hpm_srst_req(unsigned int uddr_hpm_srst_req);
int iSetPERI_PMC21ddr_hpm_uplimit(unsigned int uddr_hpm_uplimit);
int iSetPERI_PMC21ddr_hpm_lowlimit(unsigned int uddr_hpm_lowlimit);
int iSetPERI_PMC21ddr_hpm_monitor_period(unsigned int uddr_hpm_monitor_period);
int iSetPERI_PMC22mda_top_hpm_div(unsigned int umda_top_hpm_div);
int iSetPERI_PMC22mda_top_hpm_shift(unsigned int umda_top_hpm_shift);
int iSetPERI_PMC22mda_top_hpm_offset(unsigned int umda_top_hpm_offset);
int iSetPERI_PMC22mda_top_hpm_en(unsigned int umda_top_hpm_en);
int iSetPERI_PMC22mda_top_hpm_bypass(unsigned int umda_top_hpm_bypass);
int iSetPERI_PMC22mda_top_hpm_monitor_en(unsigned int umda_top_hpm_monitor_en);
int iSetPERI_PMC22mda_top_hpm_srst_req(unsigned int umda_top_hpm_srst_req);
int iSetPERI_PMC25mda_top_hpm_uplimit(unsigned int umda_top_hpm_uplimit);
int iSetPERI_PMC25mda_top_hpm_lowlimit(unsigned int umda_top_hpm_lowlimit);
int iSetPERI_PMC25mda_top_hpm_monitor_period(unsigned int umda_top_hpm_monitor_period);
int iSetPERI_PMC26vedu_hpm_div(unsigned int uvedu_hpm_div);
int iSetPERI_PMC26vedu_hpm_shift(unsigned int uvedu_hpm_shift);
int iSetPERI_PMC26vedu_hpm_offset(unsigned int uvedu_hpm_offset);
int iSetPERI_PMC26vedu_hpm_en(unsigned int uvedu_hpm_en);
int iSetPERI_PMC26vedu_hpm_bypass(unsigned int uvedu_hpm_bypass);
int iSetPERI_PMC26vedu_hpm_monitor_en(unsigned int uvedu_hpm_monitor_en);
int iSetPERI_PMC26vedu_hpm_srst_req(unsigned int uvedu_hpm_srst_req);
int iSetPERI_PMC29vedu_hpm_uplimit(unsigned int uvedu_hpm_uplimit);
int iSetPERI_PMC29vedu_hpm_lowlimit(unsigned int uvedu_hpm_lowlimit);
int iSetPERI_PMC29vedu_hpm_monitor_period(unsigned int uvedu_hpm_monitor_period);
int iSetPERI_PMC30vedu_hpm_monitor_period(unsigned int uvedu_hpm_monitor_period);
int iSetPERI_PMC30mda_top_hpm_monitor_period(unsigned int umda_top_hpm_monitor_period);
int iSetPERI_PMC30ddr_hpm_monitor_period(unsigned int uddr_hpm_monitor_period);
int iSetPERI_PMC30cpu_hpm_monitor_period(unsigned int ucpu_hpm_monitor_period);
int iSetPERI_PMC31core_hpm_monitor_period(unsigned int ucore_hpm_monitor_period);
int iSetPERI_PMC32cpu_ts_sel(unsigned int ucpu_ts_sel);
int iSetPERI_PMC32cpu_ts_dly_adjust(unsigned int ucpu_ts_dly_adjust);
int iSetPERI_PMC32cpu_ts_step(unsigned int ucpu_ts_step);
int iSetPERI_PMC32cpu_ts_en(unsigned int ucpu_ts_en);
int iSetPERI_PMC33ddr_ts_sel(unsigned int uddr_ts_sel);
int iSetPERI_PMC33ddr_ts_dly_adjust(unsigned int uddr_ts_dly_adjust);
int iSetPERI_PMC33ddr_ts_step(unsigned int uddr_ts_step);
int iSetPERI_PMC33ddr_ts_en(unsigned int uddr_ts_en);
int iSetPERI_PMC34core_ts_sel(unsigned int ucore_ts_sel);
int iSetPERI_PMC34core_ts_dly_adjust(unsigned int ucore_ts_dly_adjust);
int iSetPERI_PMC34core_ts_step(unsigned int ucore_ts_step);
int iSetPERI_PMC34core_ts_en(unsigned int ucore_ts_en);
int iSetPERI_PMC35mda_top_ts_sel(unsigned int umda_top_ts_sel);
int iSetPERI_PMC35mda_top_ts_dly_adjust(unsigned int umda_top_ts_dly_adjust);
int iSetPERI_PMC35mda_top_ts_step(unsigned int umda_top_ts_step);
int iSetPERI_PMC35mda_top_ts_en(unsigned int umda_top_ts_en);
int iSetPERI_PMC36vedu_ts_sel(unsigned int uvedu_ts_sel);
int iSetPERI_PMC36vedu_ts_dly_adjust(unsigned int uvedu_ts_dly_adjust);
int iSetPERI_PMC36vedu_ts_step(unsigned int uvedu_ts_step);
int iSetPERI_PMC36vedu_ts_en(unsigned int uvedu_ts_en);
int iSetPERI_PMC58pmu_addr(unsigned int upmu_addr);
int iSetPERI_PMC58pmu_reg_rd_all(unsigned int upmu_reg_rd_all);
int iGetPERI_PMC58pmu_reg_rd_all(unsigned int *upmu_reg_rd_all);
int iSetPERI_PMC58pmu_reg0_wt_req(unsigned int upmu_reg0_wt_req);
int iSetPERI_PMC58pmu_reg1_wt_req(unsigned int upmu_reg1_wt_req);
int iSetPERI_PMC58pmu_reg2_wt_req(unsigned int upmu_reg2_wt_req);
int iSetPERI_PMC58pmu_reg3_wt_req(unsigned int upmu_reg3_wt_req);
int iGetPERI_PMC58pmu_reg3_wt_req(unsigned int *upmu_reg3_wt_req);
int iSetPERI_PMC58pmu_reg4_wt_req(unsigned int upmu_reg4_wt_req);
int iGetPERI_PMC58pmu_reg4_wt_req(unsigned int *upmu_reg4_wt_req);
int iSetPERI_PMC58pmu_reg5_wt_req(unsigned int upmu_reg5_wt_req);
int iGetPERI_PMC58pmu_reg5_wt_req(unsigned int *upmu_reg5_wt_req);
int iSetPERI_PMC58pmu_reg6_wt_req(unsigned int upmu_reg6_wt_req);
int iSetPERI_PMC58pmu_reg7_wt_req(unsigned int upmu_reg7_wt_req);
int iGetPERI_PMC58pmu_reg7_wt_req(unsigned int *upmu_reg7_wt_req);
int iSetPERI_PMC58i2c_int_clear(unsigned int ui2c_int_clear);
int iSetPERI_PMC58pmc_i2c_enable(unsigned int upmc_i2c_enable);
int iGetPERI_PMC58pmc_i2c_enable(unsigned int *upmc_i2c_enable);
int iSetPERI_PMC59pmu_reg0(unsigned int upmu_reg0);
int iSetPERI_PMC59pmu_reg1(unsigned int upmu_reg1);
int iSetPERI_PMC59pmu_reg2(unsigned int upmu_reg2);
int iSetPERI_PMC59pmu_reg3(unsigned int upmu_reg3);
int iGetPERI_PMC59pmu_reg3(unsigned int *upmu_reg3);
int iSetPERI_PMC60pmu_reg4(unsigned int upmu_reg4);
int iGetPERI_PMC60pmu_reg4(unsigned int *upmu_reg4);
int iSetPERI_PMC60pmu_reg5(unsigned int upmu_reg5);
int iGetPERI_PMC60pmu_reg5(unsigned int *upmu_reg5);
int iSetPERI_PMC60pmu_reg6(unsigned int upmu_reg6);
int iSetPERI_PMC60pmu_reg7(unsigned int upmu_reg7);
int iSetPERI_PMC62pmc_i2c_lcnt(unsigned int upmc_i2c_lcnt);
int iSetPERI_PMC62pmc_i2c_hcnt(unsigned int upmc_i2c_hcnt);
int iSetPERI_PMC63pmu_avs_reg0_mux(unsigned int upmu_avs_reg0_mux);
int iSetPERI_PMC63pmu_avs_reg1_mux(unsigned int upmu_avs_reg1_mux);
int iSetPERI_PMC63pmu_avs_reg2_mux(unsigned int upmu_avs_reg2_mux);
int iSetPERI_PMC63pmu_avs_reg3_mux(unsigned int upmu_avs_reg3_mux);
int iSetPERI_PMC63pmu_avs_reg4_mux(unsigned int upmu_avs_reg4_mux);
int iSetPERI_PMC63pmu_avs_reg5_mux(unsigned int upmu_avs_reg5_mux);
int iSetPERI_PMC63pmu_avs_reg6_mux(unsigned int upmu_avs_reg6_mux);
int iSetPERI_PMC63pmu_avs_reg7_mux(unsigned int upmu_avs_reg7_mux);
int iSetPERI_PMC63pmu_avs_reg0_en(unsigned int upmu_avs_reg0_en);
int iSetPERI_PMC63pmu_avs_reg1_en(unsigned int upmu_avs_reg1_en);
int iSetPERI_PMC63pmu_avs_reg2_en(unsigned int upmu_avs_reg2_en);
int iSetPERI_PMC63pmu_avs_reg3_en(unsigned int upmu_avs_reg3_en);
int iSetPERI_PMC63pmu_avs_reg4_en(unsigned int upmu_avs_reg4_en);
int iSetPERI_PMC63pmu_avs_reg5_en(unsigned int upmu_avs_reg5_en);
int iSetPERI_PMC63pmu_avs_reg6_en(unsigned int upmu_avs_reg6_en);
int iSetPERI_PMC63pmu_avs_reg7_en(unsigned int upmu_avs_reg7_en);
int iSetPERI_PMC64core_ts_monitor_period(unsigned int ucore_ts_monitor_period);
int iSetPERI_PMC64core_ts_monitor_en(unsigned int ucore_ts_monitor_en);
int iSetPERI_PMC64core_ts_en_must_inc(unsigned int ucore_ts_en_must_inc);
int iSetPERI_PMC64core_avs_ctrl_sel(unsigned int ucore_avs_ctrl_sel);
int iSetPERI_PMC64core_avs_ctrl_mux(unsigned int ucore_avs_ctrl_mux);
int iSetPERI_PMC64core_ts_inc_case_sel(unsigned int ucore_ts_inc_case_sel);
int iSetPERI_PMC65cpu_ts_monitor_period(unsigned int ucpu_ts_monitor_period);
int iSetPERI_PMC65cpu_ts_monitor_en(unsigned int ucpu_ts_monitor_en);
int iSetPERI_PMC65cpu_ts_en_must_inc(unsigned int ucpu_ts_en_must_inc);
int iSetPERI_PMC65cpu_avs_ctrl_sel(unsigned int ucpu_avs_ctrl_sel);
int iSetPERI_PMC65cpu_avs_ctrl_mux(unsigned int ucpu_avs_ctrl_mux);
int iSetPERI_PMC65cpu_ts_inc_case_sel(unsigned int ucpu_ts_inc_case_sel);
int iSetPERI_PMC66ddr_ts_monitor_period(unsigned int uddr_ts_monitor_period);
int iSetPERI_PMC66ddr_ts_monitor_en(unsigned int uddr_ts_monitor_en);
int iSetPERI_PMC66ddr_ts_en_must_inc(unsigned int uddr_ts_en_must_inc);
int iSetPERI_PMC66ddr_avs_ctrl_sel(unsigned int uddr_avs_ctrl_sel);
int iSetPERI_PMC66ddr_avs_ctrl_mux(unsigned int uddr_avs_ctrl_mux);
int iSetPERI_PMC66ddr_ts_inc_case_sel(unsigned int uddr_ts_inc_case_sel);
int iSetPERI_PMC67mda_ts_monitor_period(unsigned int umda_ts_monitor_period);
int iSetPERI_PMC67mda_ts_monitor_en(unsigned int umda_ts_monitor_en);
int iSetPERI_PMC67mda_ts_en_must_inc(unsigned int umda_ts_en_must_inc);
int iSetPERI_PMC67mda_avs_ctrl_sel(unsigned int umda_avs_ctrl_sel);
int iSetPERI_PMC67mda_avs_ctrl_mux(unsigned int umda_avs_ctrl_mux);
int iSetPERI_PMC67mda_avs_hpm_sel(unsigned int umda_avs_hpm_sel);
int iSetPERI_PMC67mda_avs_ts_sel(unsigned int umda_avs_ts_sel);
int iSetPERI_PMC67mda_ts_inc_case_sel(unsigned int umda_ts_inc_case_sel);

#endif /* __PMC_H__ */
