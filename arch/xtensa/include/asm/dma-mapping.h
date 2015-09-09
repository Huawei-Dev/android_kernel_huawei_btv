/*
 * include/asm-xtensa/dma-mapping.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003 - 2005 Tensilica Inc.
 */

#ifndef _XTENSA_DMA_MAPPING_H
#define _XTENSA_DMA_MAPPING_H

#include <asm/cache.h>
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>

#define DMA_ERROR_CODE		(~(dma_addr_t)0x0)

/*
 * DMA-consistent mapping functions.
 */

extern void *consistent_alloc(int, size_t, dma_addr_t, unsigned long);
extern void consistent_free(void*, size_t, dma_addr_t);
extern void consistent_sync(void*, size_t, int);

#define dma_alloc_noncoherent(d, s, h, f) dma_alloc_coherent(d, s, h, f)
#define dma_free_noncoherent(d, s, v, h) dma_free_coherent(d, s, v, h)

void *dma_alloc_coherent(struct device *dev, size_t size,
			   dma_addr_t *dma_handle, gfp_t flag);

void dma_free_coherent(struct device *dev, size_t size,
			 void *vaddr, dma_addr_t dma_handle);

static inline dma_addr_t
dma_map_single(struct device *dev, void *ptr, size_t size,
	       enum dma_data_direction direction)
{
	BUG_ON(direction == DMA_NONE);
	consistent_sync(ptr, size, direction);
	return virt_to_phys(ptr);
}

static inline void
dma_unmap_single(struct device *dev, dma_addr_t dma_addr, size_t size,
		 enum dma_data_direction direction)
{
	BUG_ON(direction == DMA_NONE);
}

static inline int
dma_set_mask(struct device *dev, u64 mask)
{
	if(!dev->dma_mask || !dma_supported(dev, mask))
		return -EIO;

	*dev->dma_mask = mask;

	return 0;
}

static inline void
dma_cache_sync(struct device *dev, void *vaddr, size_t size,
	       enum dma_data_direction direction)
{
	consistent_sync(vaddr, size, direction);
}

/* Not supported for now */
static inline int dma_mmap_coherent(struct device *dev,
				    struct vm_area_struct *vma, void *cpu_addr,
				    dma_addr_t dma_addr, size_t size)
{
	return -EINVAL;
}

static inline int dma_get_sgtable(struct device *dev, struct sg_table *sgt,
				  void *cpu_addr, dma_addr_t dma_addr,
				  size_t size)
{
	return -EINVAL;
}

static inline void *dma_alloc_attrs(struct device *dev, size_t size,
				    dma_addr_t *dma_handle, gfp_t flag,
				    struct dma_attrs *attrs)
{
	return NULL;
}

static inline void dma_free_attrs(struct device *dev, size_t size,
				  void *vaddr, dma_addr_t dma_handle,
				  struct dma_attrs *attrs)
{
}

#endif	/* _XTENSA_DMA_MAPPING_H */
