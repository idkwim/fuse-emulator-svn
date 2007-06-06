/* ula.h: ULA routines
   Copyright (c) 1999-2004 Philip Kendall, Darren Salt

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#ifndef FUSE_ULA_H
#define FUSE_ULA_H

/* How much contention do we get at every tstate? */
extern libspectrum_byte ula_contention[ 80000 ];

libspectrum_byte ula_read( libspectrum_word port, int *attached );
void ula_write( libspectrum_word port, libspectrum_byte b );

libspectrum_byte ula_last_byte( void );

libspectrum_byte ula_tape_level( void );

int ula_from_snapshot( libspectrum_snap *snap );
int ula_to_snapshot( libspectrum_snap *snap );

void ula_contend_port_early( libspectrum_word port );
void ula_contend_port_late( libspectrum_word port );

#endif			/* #ifndef FUSE_ULA_H */