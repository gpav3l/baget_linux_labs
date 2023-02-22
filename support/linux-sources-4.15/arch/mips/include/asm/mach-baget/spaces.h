#ifndef _ASM_MACH_BAGET_SPACES_H
#define _ASM_MACH_BAGET_SPACES_H

#ifdef CONFIG_64BIT

#define PHYS_OFFSET		_AC(0x0000000040000000, UL)
#define UNCAC_BASE		(_AC(0x9000000000000000, UL) + PHYS_OFFSET)

#define __pa_symbol(x)	(PHYS_OFFSET + __pa(RELOC_HIDE((unsigned long)(x), 0)))

#endif /* CONFIG_64BIT */

#include <asm/mach-generic/spaces.h>

#endif /* __ASM_MACH_BAGET_SPACES_H */
