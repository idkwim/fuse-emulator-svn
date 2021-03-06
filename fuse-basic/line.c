/* line.c: routines for dealing with a program line
   Copyright (c) 2002-2003 Philip Kendall

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

#include "config.h"

#include <stdlib.h>

#include <glib.h>

#include "line.h"
#include "statement.h"

error_t
line_append_statement( struct line *line, struct statement *statement )
{
  line->statements = g_slist_append( line->statements, (gpointer)statement );
  return BASIC_ERROR_NONE;
}

void
line_free( gpointer data, gpointer user_data )
{
  struct line *line = data;

  g_slist_foreach( line->statements, statement_free, NULL );
  g_slist_free( line->statements );
  free( line );
}
