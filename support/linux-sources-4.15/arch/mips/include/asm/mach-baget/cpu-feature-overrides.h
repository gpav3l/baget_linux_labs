/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_MACH_BAGET_CPU_FEATURE_OVERRIDES_H
#define __ASM_MACH_BAGET_CPU_FEATURE_OVERRIDES_H

#define cpu_has_tlb		1
#define cpu_has_tlbinv		0
#define cpu_has_htw		0
#define cpu_has_maar		0
#define cpu_has_3k_cache	0
#define cpu_has_4k_cache	1
#define cpu_has_tx39_cache	0
#define cpu_has_32fpr		1
#define cpu_has_counter		1
#define cpu_has_watch		1
#define cpu_has_divec		1
#define cpu_has_vce		0
#define cpu_has_cache_cdex_p	0
#define cpu_has_cache_cdex_s	0
#define cpu_has_prefetch	1
#define cpu_has_mcheck		1
#define cpu_has_ejtag		0
#define cpu_has_llsc		1
#define cpu_has_mips16		0
#define cpu_has_mdmx		0
#define cpu_has_mips3d		0
#define cpu_has_smartmips	0
#define cpu_has_mmips		0
#define cpu_has_vtag_icache	0
#define cpu_has_dc_aliases	0
#define cpu_has_ic_fills_f_dc	0
#define cpu_has_dsp		0
#define cpu_has_mipsmt		0
#define cpu_has_nofpuex		0
#define cpu_has_64bits		1
#define cpu_has_64bit_zero_reg	1
#define cpu_has_inclusive_pcaches	0

#define cpu_dcache_line_size()	32
#define cpu_icache_line_size()	32
#define cpu_scache_line_size()	32

#define cpu_has_cpca	(current_cpu_data.ases & MIPS_ASE_CPCA)
#define cpu_has_cpv	(current_cpu_data.ases & MIPS_ASE_CPV)

#endif /* __ASM_MACH_BAGET_CPU_FEATURE_OVERRIDES_H */
