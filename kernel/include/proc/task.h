/**
 *  kernel/include/proc/task.h
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
#ifndef _TASK_H
#define _TASK_H

#include <sys/types.h>
#include <stdint.h>

#include <proc/proc.h>
// #include <proc/thread.h>
#include <iostream.h>

struct thread;

typedef struct task {
  proc_t *proc;
  iostream_t *iostream;
  
  uint32_t num_threads;
  struct thread **threads;
} task_t;

task_t *create_task(void *entry, char *name);
int exit_task(task_t task, int status);
int kill_task(task_t task, int status);

#endif
