/*                                                      -*- c -*-
   Win32 config.h
   Copyright (C) 1999-2000, Peter Boos <pedib@colorfullife.com>
   Copyright (C) 2002-2006, Joe Orton <joe@manyfish.co.uk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

*/
#if defined(_WIN32) && !defined(WIN32)
#define WIN32
#endif

#ifdef WIN32

#define NEON_VERSION "0.29.6"
#define NE_VERSION_MAJOR (0)
#define NE_VERSION_MINOR (29)

#define HAVE_ERRNO_H
#define HAVE_LIMITS_H
#define HAVE_STDLIB_H
#define HAVE_STRING_H

#define HAVE_MEMCPY
#define HAVE_SETSOCKOPT

#define HAVE_SSPI

/* Define to enable debugging */
#define NE_DEBUGGING 1

#define NE_FMT_SIZE_T "u"
#define NE_FMT_SSIZE_T "d"
#define NE_FMT_OFF_T "lld"
#define NE_FMT_NE_OFF_T NE_FMT_OFF_T

#ifndef NE_FMT_XML_SIZE
#define NE_FMT_XML_SIZE "d"
#endif

/* needs adjusting for Win64... */
#define SIZEOF_INT 4
#define SIZEOF_LONG 4

/* Win32 uses a underscore, so we use a macro to eliminate that. */
#define snprintf			_snprintf
/* VS2008 has this already defined */
#if (_MSC_VER < 1500)
#define vsnprintf			_vsnprintf
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define strcasecmp			_strcmpi
#define strncasecmp			_strnicmp
#else
#define strcasecmp			strcmpi
#define strncasecmp			strnicmp
#endif
#define ssize_t				int
#define inline                          __inline
#define off_t                           _off_t

#ifndef USE_GETADDRINFO
#define in_addr_t                       unsigned int
#endif

typedef int socklen_t;

#include <io.h>
#define read _read

#endif
