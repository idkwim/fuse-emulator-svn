/* widget.h: Simple dialog boxes for all user interfaces.
   Copyright (c) 2001,2002 Matan Ziv-Av, Philip Kendall

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

#ifndef FUSE_WIDGET_H
#define FUSE_WIDGET_H

#ifndef _DIRENT_H
#include <dirent.h>
#endif				/* #ifndef _DIRENT_H */

#ifndef FUSE_KEYBOARD_H
#include "keyboard.h"
#endif				/* #ifndef FUSE_KEYBOARD_H */

/* The default colours used in the widget */
#define WIDGET_COLOUR_BACKGROUND 1	/* Blue */
#define WIDGET_COLOUR_FOREGROUND 7	/* White */

/* The various widgets which are available */
typedef enum widget_type {

  WIDGET_TYPE_FILESELECTOR,	/* File selector */
  WIDGET_TYPE_GENERAL,		/* General options */
  WIDGET_TYPE_TAPE,		/* Tape menu */
  WIDGET_TYPE_FILE,		/* File menu */
  WIDGET_TYPE_MACHINE,		/* Machine menu */
  WIDGET_TYPE_PICTURE,		/* Keyboard picture */
  WIDGET_TYPE_HELP,		/* Help menu */
  WIDGET_TYPE_MENU,		/* General menu */

} widget_type;

/* The ways of finishing a widget */
typedef enum widget_finish_state {
  WIDGET_FINISHED_OK = 1,
  WIDGET_FINISHED_CANCEL,
} widget_finish_state;

/* A general menu */
typedef struct widget_menu_entry {
  const char *text;		/* Menu entry text */
  keyboard_key_name key;	/* Which key to activate this widget */
  widget_type widget;		/* Which widget to call */
  void *widget_args;		/* And with which arguments */
} widget_menu_entry;

/* A function to draw a widget */
typedef int (*widget_draw_fn)( void *data );

/* A function to handle keypresses */
typedef void (*widget_keyhandler_fn)( int key );

/* The information we need to store for each widget */
typedef struct widget_t {
  widget_draw_fn draw;			/* Draw this widget */
  int (*finish)( widget_finish_state finished ); /* Post-widget processing */
  widget_keyhandler_fn keyhandler;	/* Keyhandler */
} widget_t;

/* The information we need to store to recurse from a widget */
typedef struct widget_recurse_t {

  widget_type type;		/* Which type of widget are we? */
  void *data;			/* What data were we passed? */

  int finished;			/* Have we finished this widget yet? */

} widget_recurse_t;

/* A `stack' so we can recurse through widgets */
extern widget_recurse_t widget_return[];

/* How many levels deep have we recursed through widgets; -1 => none */
extern int widget_level;

/* The current widget keyhandler */
widget_keyhandler_fn widget_keyhandler;

int widget_init( void );
int widget_end( void );

int widget_do( widget_type which, void *data );

int widget_timer_init( void );
int widget_timer_end( void );

void widget_rectangle( int x, int y, int w, int h, int col );
void widget_printstring( int x, int y, int col, const char *s );

extern widget_finish_state widget_finished;;

int widget_dialog( int x, int y, int width, int height );
int widget_dialog_with_border( int x, int y, int width, int height );

/* File selector */

typedef struct widget_dirent {
  int mode;
  char *name;
} widget_dirent;

struct widget_dirent **widget_filenames;
size_t widget_numfiles;

int widget_filesel_draw( void* data );
int widget_filesel_finish( widget_finish_state finished );
void widget_filesel_keyhandler( int key );

extern char* widget_filesel_name;

/* General options */

int widget_general_draw( void* data );
int widget_general_finish( widget_finish_state finished );
void widget_general_keyhandler( int key );

/* Tape menu */

int widget_tape_draw( void* data );
void widget_tape_keyhandler( int key );

/* File menu */

int widget_file_draw( void* data );
void widget_file_keyhandler( int key );

/* Machine menu */

int widget_machine_draw( void* data );
void widget_machine_keyhandler( int key );

/* Keyboard picture */

int widget_picture_draw( void* data );
void widget_picture_keyhandler( int key );

/* The data for the keyboard picture */

extern BYTE widget_keyboard_picture[6912];

/* Help menu */

int widget_help_draw( void* data );
void widget_help_keyhandler( int key );

/* General menu code */

int widget_menu_draw( void* data );
void widget_menu_keyhandler( int key );

/* Available menus */

extern widget_menu_entry widget_menu_main[];
extern widget_menu_entry widget_menu_options[];

/* The widgets actually available */

extern widget_t widget_data[];

#endif				/* #ifndef FUSE_WIDGET_H */
