/*
 * HI SoC specific OPP Data helpers
 *
 */
#ifndef __HI_OPP_DATA_H__
#define __HI_OPP_DATA_H__

#include <linux/cpufreq.h>

struct hi_opp_def
{
    unsigned long freq;
    unsigned long u_volt;

    bool default_available;
};

/*
 * Initialization wrapper used to define an OPP for OMAP variants.
 */
#define OPP_INITIALIZER(_enabled, _freq, _uv)   \
    {                               \
        .default_available = _enabled,         \
        .freq = _freq,                \
        .u_volt = _uv,                  \
    }

int  PM_FreqtableInit(struct device *dev, 
                                struct cpufreq_frequency_table **table);
void PM_FreqtableExit(struct device *dev, 
                                    struct cpufreq_frequency_table **table);

int  PM_OppInitTable(struct device *device, struct hi_opp_def *opp_def, 
                                unsigned int opp_def_size);



#endif      /* __ARCH_ARM_MACH_HI_OPP_DATA_H */
