/* dck.c: dock snapshot (Warajevo .DCK) handling routines
   Copyright (c) 2003 Darren Salt, Fredrick Meunier, Philip Kendall

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

   Author contact information:

   Philip: pak21-fuse@srcf.ucam.org
   Postal address: 15 Crescent Road, Wokingham, Berks, RG40 2DB, England

   Darren: linux@youmustbejoking.demon.co.uk
   Fred: fredm@spamcop.net

*/

#include <config.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <libspectrum.h>

#include "dck.h"
#include "machine.h"
#include "settings.h"
#include "scld.h"
#include "tc2068.h"
#include "ui/ui.h"
#include "utils.h"
#include "debugger/debugger.h"
#include "widget/widget.h"

int
dck_insert( const char *filename )
{
  int error;

  error = settings_set_string( &settings_current.dck_file, filename );
  if( error ) return error;

  error = dck_read( filename ); if( error ) return error;

  machine_reset();

  return 0;
}

void
dck_eject( void )
{
  if ( !( libspectrum_machine_capabilities( machine_current->machine ) &
	  LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_DOCK ) ) {
    ui_error( UI_ERROR_ERROR, "This machine does not support the dock" );
    return;
  }

  if( settings_current.dck_file ) free( settings_current.dck_file );
  settings_current.dck_file = NULL;

  ui_menu_activate( UI_MENU_ITEM_MEDIA_CARTRIDGE_EJECT, 0 );

  machine_reset();
}

int
dck_read( const char *filename )
{
  utils_file file;
  size_t num_block = 0;
  libspectrum_dck *dck;
  int error;

  int i;
  memory_page *mem;

  if ( !( libspectrum_machine_capabilities( machine_current->machine ) &
	  LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_DOCK ) ) {
    ui_error( UI_ERROR_ERROR, "This machine does not support the dock" );
    return 1;
  }

  error = libspectrum_dck_alloc( &dck ); if( error ) return error;

  error = utils_read_file( filename, &file );
  if( error ) { libspectrum_dck_free( dck, 0 ); return error; }

  error = libspectrum_dck_read2( dck, file.buffer, file.length, filename );
  if( error ) {
    utils_close_file( &file ); libspectrum_dck_free( dck, 0 ); return error;
  }

  if( utils_close_file( &file ) ) {
    libspectrum_dck_free( dck, 0 );
    return 1;
  }

  while( dck->dck[num_block] != NULL ) {
    switch( dck->dck[num_block]->bank ) {
    case LIBSPECTRUM_DCK_BANK_HOME:
      mem = timex_home;
      break;
    case LIBSPECTRUM_DCK_BANK_DOCK:
      mem = timex_dock;
      break;
    case LIBSPECTRUM_DCK_BANK_EXROM:
      mem = timex_exrom;
      break;
    default:
      ui_error( UI_ERROR_INFO, "Sorry, bank ID %i is unsupported",
		dck->dck[num_block]->bank );
      libspectrum_dck_free( dck, 0 );
      return 1;
    }

    for( i = 0; i < 8; i++ ) {
      switch( dck->dck[num_block]->access[i] ) {

      case LIBSPECTRUM_DCK_PAGE_NULL:
        break;

      case LIBSPECTRUM_DCK_PAGE_ROM:
        mem[i].page = dck->dck[num_block]->pages[i];
        mem[i].allocated = 1;
        mem[i].writable = 0;
	mem[i].reverse = -1;
        break;

      case LIBSPECTRUM_DCK_PAGE_RAM_EMPTY:
      case LIBSPECTRUM_DCK_PAGE_RAM:
        if( dck->dck[num_block]->bank == LIBSPECTRUM_DCK_BANK_HOME && i > 1 ) {
          /* Because the scr and snapshot code depends on the standard memory
             map being in the RAM[] array, we copy blocks from the HOME bank
             into the appropriate page via the timex_home structure */
          memcpy( mem[i].page, dck->dck[num_block]->pages[i], 0x2000 );
          free( dck->dck[num_block]->pages[i] );
        } else {
          mem[i].page = dck->dck[num_block]->pages[i];
          mem[i].allocated = 1;
          mem[i].writable = 1;
	  mem[i].reverse = -1;
        }

        break;

      }
    }
    num_block++;
  }

  /* Make the menu item to eject the cartridge active */
  ui_menu_activate( UI_MENU_ITEM_MEDIA_CARTRIDGE_EJECT, 1 );

  /* Don't deallocate the memory banks! */
  return libspectrum_dck_free( dck, 1 );
}
