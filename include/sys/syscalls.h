/**
 *  include/sys/syscalls.h
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
#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#define SYSCALL_EXIT 0x00 /* exit */
#define SYSCALL_PUTC 0x01 /* put char   */
#define SYSCALL_PUTS 0x02 /* put string */
#define SYSCALL_GETC 0x03 /* get char   */
#define SYSCALL_GETS 0x04 /* get string */
#define SYSCALL_TIME 0x05 /* get datetime */

#endif
