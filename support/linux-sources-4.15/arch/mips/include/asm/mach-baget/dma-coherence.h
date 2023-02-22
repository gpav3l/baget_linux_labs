/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2006 Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) 2010 Gleb O. Raiko
 * Copyright (C) 2015 Peter Mamonov <pmamonov@gmail.com>
 */

#ifndef __ASM_MACH_BAGET_DMA_COHERENCE_H
#define __ASM_MACH_BAGET_DMA_COHERENCE_H

#define BAGET_LMEM_SIZE	(256 << 20)
#define BAGET_HMEM_BASE	0x40000000

static inline dma_addr_t baget_swizzle_dma_addr(dma_addr_t daddr)
{
	if (PHYS_OFFSET || daddr >= BAGET_HMEM_BASE)
		daddr -= BAGET_HMEM_BASE;
	return daddr;
}

static inline dma_addr_t plat_map_dma_mem(struct device *dev, void *addr,
				size_t size)
{
	dma_addr_t daddr = virt_to_phys(addr);

	return baget_swizzle_dma_addr(daddr);
}

static inline dma_addr_t plat_map_dma_mem_page(struct device *dev,
				struct page *page)
{
	dma_addr_t daddr = page_to_phys(page);

	return baget_swizzle_dma_addr(daddr);
}

static inline unsigned long plat_dma_addr_to_phys(struct device *dev,
				dma_addr_t dma_addr)
{
	if (PHYS_OFFSET || dma_addr >= BAGET_LMEM_SIZE)
		dma_addr += BAGET_HMEM_BASE;
	return dma_addr;
}

static inline void plat_unmap_dma_mem(struct device *dev, dma_addr_t dma_addr,
			size_t size, enum dma_data_direction direction)
{
}

static inline int plat_dma_supported(struct device *dev, u64 mask)
{
	return 1;
}

static inline int plat_device_is_coherent(struct device *dev)
{
	return 0;
}

static inline void plat_post_dma_flush(struct device *dev)
{
}

#endif /* __ASM_MACH_BAGET_DMA_COHERENCE_H */
