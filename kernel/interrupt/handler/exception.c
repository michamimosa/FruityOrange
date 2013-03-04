/**
 *  kernel/interrupt/handler/exception.c
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
#include <stddef.h>

#include <interrupt.h>
#include <debug/panic.h>
#include <driver/console.h>
#include <cpu.h>

const char *exception_msg[] = {
  "Divide by Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Overflow",
  "Bound Range",
  "Invalid Opcode",
  "Device Not Aviable",
  "Double Fault",
  "Coprocessor Segment Overrun",
  "Invalid TTS",
  "Segment not Present",
  "Stack Fault",
  "General Protection",
  "Page Fault",
  "Reserved Interrupt",
  "x87 Floating Point",
  "Alignment Check",
  "Machine Check",
  "SIMD Floating Point",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
  "Reserved Interrupt",
};

cpu_state_t* handle_exception(cpu_state_t *cpu) {
  new_cpu = cpu;
  
  uint32_t cr0, cr2, cr3;
  asm volatile("mov %%cr0, %0" : "=r" (cr0));
  asm volatile("mov %%cr2, %0" : "=r" (cr2));
  asm volatile("mov %%cr3, %0" : "=r" (cr3));
  setColor(0xf4);
  printf("Exception occurred: #%s!\n",exception_msg[cpu->intr]);
  printf("CPU-Dump:\n"
	 "EAX = 0x%x  EBX = 0x%x  ECX = 0x%x  EDX = 0x%x\n"
	 "ESI = 0x%x  EDI = 0x%x  EBP = 0x%x  ESP = 0x%x\n"
	 "EIP = 0x%x   CS = 0x%x   SS = 0x%x\n"
	 " DS = 0x%x   ES = 0x%x   FS = 0x%x   GS = 0x%x\n"
	 "CR0 = 0x%x  CR2 = 0x%x  CR3 = 0x%x\n"
	 "EFLAGS = 0x%x  INTR = 0x%4x  ERRORCODE = 0x%x\n"
	 "Kernel stopped.",
	 cpu->eax, cpu->ebx, cpu->ecx, cpu->edx,
	 cpu->esi, cpu->edi, cpu->ebp, cpu->esp,
	 cpu->eip, cpu->cs,  cpu->ss,
	 cpu->ds,  cpu->es,  cpu->fs,  cpu->gs,
	 cr0, cr2, cr3,
	 cpu->eflags, cpu->intr, cpu->error_code);
  
  while(1) {
    // TODO solve problem
    asm volatile("cli; hlt");
  }
  
  return new_cpu;
}