/**
 *  kernel/include/mm.h
 *
 *  (C) Copyright 2012-2013 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _MM_H
#define _MM_H

#include <stdint.h>
#include <stddef.h>
#include <multiboot.h>

#define PMM_FREE 1
#define PMM_USED 0
#define PAGE_SIZE 0x1000
#define PD_SIZE 1024
#define PT_SIZE 1024

#define PAGE_MASK 0xfffff000

#define PAGE_INDEX(x) (x / PAGE_SIZE)
#define PD_INDEX(x) (x / PT_SIZE)
#define PT_INDEX(x) (x % PT_SIZE)

#define VMM_PRESENT 0x01
#define VMM_WRITE   0x02
#define VMM_USER    0x04
#define VMM_KERNEL_FLAGS (VMM_PRESENT | VMM_WRITE)
#define VMM_USER_FLAGS   (VMM_PRESENT | VMM_WRITE | VMM_USER)

extern const void kernel_start_phys;
extern const void kernel_start_virt;
extern const void kernel_end_phys;
extern const void kernel_end_virt;

#define KERNEL_SIZE ((uintptr_t) &kernel_end_phys)
#define KERNEL_PAGES ((KERNEL_SIZE+PAGE_SIZE) / PAGE_SIZE)

#define NUM_PAGES(n) ((((n) + ~PAGE_MASK) & PAGE_MASK) / PAGE_SIZE)

#define VADDR_USER_START ((uintptr_t) 0x00001000)
#define VADDR_USER_END   ((uintptr_t) 0xbfffffff)
#define VADDR_USER_HEAP_START ((uintptr_t) 0xa0000000)
#define VADDR_USER_HEAP_END   ((uintptr_t) 0xafffffff)
#define VADDR_USER_STACK_TOP ((uintptr_t) 0xc0000000)
#define VADDR_KERNEL_START ((uintptr_t) 0xc0000000)
#define VADDR_KERNEL_END   ((uintptr_t) 0xffffffff)
#define VADDR_KERNEL_HEAP_START ((uintptr_t) 0xe0000000)
#define VADDR_KERNEL_HEAP_END   ((uintptr_t) 0xefffffff)
#define VADDR_PT_START ((uintptr_t)   0xf0000000)

#define PT_PADDR(c, i) (c->pagedir[i] & PAGE_MASK)
#define PT_VADDR(i) (VADDR_PT_START + PAGE_SIZE*i)

#define FOR_KERNEL_PTS(i) \
  for(i = PD_INDEX(PAGE_INDEX(VADDR_KERNEL_START)); \
      i < PD_INDEX(PAGE_INDEX(VADDR_KERNEL_END)); i++)

typedef uint32_t* vmm_pd_t;
typedef uint32_t* vmm_pt_t;

typedef struct vmm_context {
  vmm_pd_t pagedir;
  uintptr_t pagedir_paddr;
} vmm_context_t;

typedef struct alloc_block {
  size_t size;
  void *base;
  int status;
  
  struct alloc_block *prev;
  struct alloc_block *next;
} alloc_block_t;

void mm_init_syscalls(void);

void syscall_malloc_pages(uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
void syscall_mfree_pages(uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

// pmm
void init_pmm(multiboot_info_t *mb_info);
void *pmm_alloc(void);
void pmm_free(void *ptr);
void pmm_mark_used(void *ptr);

// vmm
void init_vmm(multiboot_info_t *mb_info);
inline void vmm_enable(void);
inline void vmm_disable(void);
vmm_pt_t vmm_create_pagetable(vmm_context_t *context, int index, uint8_t flags);
vmm_pt_t vmm_get_pagetable(vmm_context_t *context, int index, uint8_t flags);
vmm_context_t *vmm_create_context(void);
vmm_context_t *vmm_fork(vmm_context_t *context);
int vmm_map_page(vmm_context_t *context, uintptr_t vaddr, uintptr_t paddr, uint8_t flags);
int vmm_unmap_page(vmm_context_t *context, uintptr_t vaddr);
int vmm_map_area(vmm_context_t *context, uintptr_t vaddr, uintptr_t paddr, size_t pages, uint8_t flags);
int vmm_unmap_area(vmm_context_t *context, uintptr_t vaddr, size_t pages);
void *vmm_find(vmm_context_t *context, size_t num, uintptr_t limit_low, uintptr_t limit_high);
void *vmm_automap_kernel_page(vmm_context_t *context, uintptr_t paddr);
void *vmm_automap_kernel_area(vmm_context_t *context, uintptr_t paddr, size_t pages);
void *vmm_automap_user_page(vmm_context_t *context, uintptr_t paddr);
void *vmm_automap_user_area(vmm_context_t *context, uintptr_t paddr, size_t pages);
void *vmm_alloc(void);
void *vmm_alloc_area(size_t pages);
uintptr_t vmm_paddr(vmm_context_t *context, uintptr_t vaddr);
inline void vmm_update_context(vmm_context_t *context);
inline void vmm_activate_context(vmm_context_t *context);
inline void vmm_flush_tlb(uintptr_t vaddr);
#ifndef _VMM_C
extern vmm_context_t *current_context;
extern vmm_context_t *kernel_context;
#endif

int pagefault(uint32_t cr0, uint32_t cr2, uint32_t cr3);

// heap

#define HEAP_STATUS_FREE 0
#define HEAP_STATUS_USED 1

void init_heap(void);
void *heap_pages(size_t pages);
alloc_block_t *heap_increase(size_t pages);
alloc_block_t *heap_insert_block(alloc_block_t *block);
alloc_block_t *heap_find_block(void *ptr);
void *malloc(size_t bytes);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t bytes);
void free(void *ptr);

#endif
