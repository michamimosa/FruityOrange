/**
 *  include/proc/scheduler.h
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
#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdint.h>
#include <cpu.h>
#include <proc/proc.h>

void init_scheduler(void);
void scheduler_init_syscalls(void);
void schedule(void);
void idle(void);

#ifndef _SCHEDULER_C
extern proc_t *current_proc;
#endif

#endif
