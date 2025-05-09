/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2002, 2004, 2007 by Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) 2008 Cavium Networks <support@caviumnetworks.com>
 */
#ifndef __ASM_MIPS_MACH_CAVIUM_OCTEON_WAR_H
#define __ASM_MIPS_MACH_CAVIUM_OCTEON_WAR_H

#define R4600_V1_INDEX_ICACHEOP_WAR	0
#define R4600_V1_HIT_CACHEOP_WAR	0
#define R4600_V2_HIT_CACHEOP_WAR	0
#define R5432_CP0_INTERRUPT_WAR		0
#define BCM1250_M3_WAR			0
#define SIBYTE_1956_WAR			0
#define MIPS4K_ICACHE_REFILL_WAR	0
#define MIPS_CACHE_SYNC_WAR		0
#define TX49XX_ICACHE_INDEX_INV_WAR	0
#define ICACHE_REFILLS_WORKAROUND_WAR	0
#define R10000_LLSC_WAR			0
#define MIPS34K_MISSED_ITLB_WAR		0
#define SRISA_K64P_ULR_WAR		0

#define CAVIUM_OCTEON_DCACHE_PREFETCH_WAR	\
	OCTEON_IS_MODEL(OCTEON_CN6XXX)

#endif /* __ASM_MIPS_MACH_CAVIUM_OCTEON_WAR_H */
