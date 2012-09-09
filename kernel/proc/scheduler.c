/**
 *  kernel/proc/scheduler.c
 *
 *  (C) Copyright 2012 Michael Sippel
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
#include <stdint.h>

#include <cpu.h>
#include <mm.h>
#include <interrupt.h>
#include <proc/scheduler.h>
#include <proc/proc.h>

static proc_t *current_proc = NULL;
extern proc_t *first_proc;

void init_scheduler(void) {
  set_irq_handler(0x0, schedule);
}

void schedule(void) {
  if(current_proc != NULL) {
    cpu_state_t *cpu = get_cpu_state();
    current_proc->cpu = cpu;
    
    current_proc = current_proc->next;
    
    cpu_state_t *new_cpu = current_proc->cpu;
    if(cpu != new_cpu) {
      set_cpu_state(new_cpu);
    }
  } else {
    if(first_proc != NULL) {
      current_proc = first_proc;
      set_cpu_state(current_proc->cpu);
    }
  }
  common_eoi(0x20);
}
