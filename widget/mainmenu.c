/* mainmenu.c: Main menu widget
   Copyright (c) 2001 Philip Kendall

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

   E-mail: pak21-fuse@srcf.ucam.org
   Postal address: 15 Crescent Road, Wokingham, Berks, RG40 2DB, England

*/

#include <config.h>

#include <unistd.h>

#include "display.h"
#include "keyboard.h"
#include "ui.h"
#include "uidisplay.h"
#include "widget.h"

int widget_mainmenu_draw( void )
{
  /* Draw the dialog box */
  widget_dialog_with_border( 1, 2, 30, 2 );

  widget_printstring( 2, 2, WIDGET_COLOUR_FOREGROUND,
		      "General (o)ptions" );

  widget_printstring( 2, 3, WIDGET_COLOUR_FOREGROUND,
		      "(T)ape control" );

  uidisplay_lines( DISPLAY_BORDER_HEIGHT + 16,
		   DISPLAY_BORDER_HEIGHT + 16 + 16 );

  return 0;
}

void widget_mainmenu_keyhandler( int key )
{
  switch( key ) {
    
  case KEYBOARD_1: /* 1 used as `Escape' generates `Edit', which is Caps + 1 */
    widget_return[ widget_level ].finished = WIDGET_FINISHED_CANCEL;
    break;

  case KEYBOARD_o:
    widget_do( WIDGET_TYPE_OPTIONS );
    break;

  case KEYBOARD_t:
    widget_do( WIDGET_TYPE_TAPE );
    break;

  case KEYBOARD_Enter:
    widget_return[ widget_level ].finished = WIDGET_FINISHED_OK;
    break;

  }
}
