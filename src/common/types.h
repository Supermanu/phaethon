/* Phaethon - A FLOSS resource explorer for BioWare's Aurora engine games
 *
 * Phaethon is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * Phaethon is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * Phaethon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Phaethon. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Low-level type definitions to handle fixed width types portably.
 */

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <cstddef>
#include <climits>

#ifdef HAVE_INTTYPES_H
	#include <inttypes.h>
#endif // HAVE_INTTYPES_H
#ifdef HAVE_STDINT_H
	#include <stdint.h>
#endif // HAVE_STDINT_H
#ifdef HAVE_SYS_TYPES_H
	#include <sys/types.h>
#endif // HAVE_SYS_TYPES_H

#if defined(HAVE_INTTYPES_H) || defined(HAVE_STDINT_H)
	/* If either of these is available, the C99 integer types are
	   available. Furthermore <inttypes.h> should even already
	   include <stdint.h>. */
#elif defined(HAVE_SYS_TYPES_H)
	/* <sys/types.h> should define signed integer types just like
	   C99. However, the unsigned ones are usually named a bit
	   differently.

	   TODO: This might be different on some platforms!
	*/
	typedef u_int8_t  uint8_t;
	typedef u_int16_t uint16_t;
	typedef u_int32_t uint32_t;
	typedef u_int64_t uint64_t;
#else
	// TODO: Add a fall-back type detection to the configure script.
	#error Cannot find a way to derive fixed-width integer types
#endif

// The maximum value a size_t can describe
#ifndef SIZE_MAX
	#define SIZE_MAX ((size_t) -1)
#endif

// Fallback macro to printf an int64. A bit wonky; usage discouraged.
#ifndef PRId64
	#define PRId64   "lld"
	#define Cd64(x)  ((signed long long) (x))
#else
	#define Cd64(x)  ((int64) (x))
#endif

// Fallback macro to printf an uint64. A bit wonky; usage discouraged.
#ifndef PRIu64
	#define PRIu64   "llu"
	#define Cu64(x)  ((unsigned long long) (x))
#else
	#define Cu64(x)  ((uint64) (x))
#endif

/* Shorter type definitions we inherited from ScummVM.
   Right now, we're keeping them to stay somewhat compatible
   with ScummVM and ResidualVM, to foster easier code exchange.

   TODO: We might maybe want to think about completely migrating
   to just the standard C99 types. Such a change will be a bit
   messy, though.
*/
typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

// Type to indicate that this is a raw byte (or an array of raw bytes, ...).
typedef uint8 byte;
// Convenience type definition for a simple unsigned int.
typedef unsigned int uint;

// Fallback macro to create an int64 constant.
#ifndef INT64_C
	#define INT64_C(c) (c ## LL)
#endif

// Fallback macro to create an uint64 constant.
#ifndef UINT64_C
	#define UINT64_C(c) (c ## ULL)
#endif

#endif // COMMON_TYPES_H
