/**
 *  include/stdarg.h
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
#ifndef _STDARG_H_
#define _STDARG_H_

typedef __builtin_va_list va_list;
#define va_start(ap, X)   __builtin_va_start(ap, X)
#define va_arg(ap, type)  __builtin_va_arg(ap, type)
#define va_end(ap)        __builtin_va_end(ap)

#endif
