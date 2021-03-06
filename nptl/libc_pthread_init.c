/* Copyright (C) 2002-2021 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <unistd.h>
#include <list.h>
#include <register-atfork.h>
#include <dl-sysdep.h>
#include <tls.h>
#include <string.h>
#include <pthreadP.h>
#include <libc-lock.h>
#include <sysdep.h>
#include <ldsodefs.h>


#ifdef TLS_MULTIPLE_THREADS_IN_TCB
void
#else
extern int __libc_multiple_threads attribute_hidden;

int *
#endif
__libc_pthread_init (void (*reclaim) (void))
{
  /* Called by a child after fork.  */
  __register_atfork (NULL, NULL, reclaim, NULL);

#ifndef TLS_MULTIPLE_THREADS_IN_TCB
  return &__libc_multiple_threads;
#endif
}
