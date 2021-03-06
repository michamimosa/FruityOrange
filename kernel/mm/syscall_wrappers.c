/**
 *  kernel/mm/syscall_wrappers.c
 *
 *  (C) Copyright 2013 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <sys/syscalls.h>
#include <stdint.h>

#include <debug/debug.h>
#include <proc/scheduler.h>
#include <proc/proc.h>
#include <syscall.h>
#include <mm.h>

void mm_init_syscalls(void) {
  setup_syscall(SYSCALL_MALLOC, "malloc", &syscall_malloc_pages);
  setup_syscall(SYSCALL_MFREE, "free", &syscall_mfree_pages);
}

void syscall_malloc_pages(uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
  size_t pages = *ebx;
  
  uintptr_t vaddr_start = (uintptr_t) vmm_find(current_context, pages, VADDR_USER_HEAP_START, VADDR_USER_HEAP_END);
  
  int i;
  for(i = 0; i < pages; i++) {
    uintptr_t vaddr = vaddr_start + i*PAGE_SIZE;
    uintptr_t paddr = (uintptr_t) pmm_alloc();
    vmm_map_page(current_context, vaddr, paddr, VMM_USER_FLAGS);
  }
  
  *ecx = vaddr_start;
  current_proc->used_mem_pages += pages;
}

void syscall_mfree_pages(uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
  vmm_unmap_area(current_context, *ebx, *ecx);
  current_proc->used_mem_pages -= *ecx;
}

