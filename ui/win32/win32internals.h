/* win32internals.h: stuff internal to the Win32 UI
   Copyright (c) 2004 Marek Januszewski

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

#ifndef FUSE_WIN32INTERNALS_H
#define FUSE_WIN32INTERNALS_H

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h>

#include <libspectrum.h>

#define ID_STATUSBAR 900

/* window handler */
HWND fuse_hWnd;

/* application instance */
HINSTANCE fuse_hInstance;

/* status bar handle */
HWND fuse_hStatusWindow;

/* pokefinder window handle */
HWND fuse_hPFWnd;

/* debugger window handle */
HWND fuse_hDBGWnd;

/*
 * Display routines (win32display.c)
 */

/* The colour palette in use */
extern libspectrum_dword win32display_colours[16];

int win32display_init( void );
int win32display_end( void );

/* Below variables and functions are shared
   between win32display.c and win32ui.c */
extern int fuse_nCmdShow;

extern int win32display_sizechanged;

void win32display_resize( int size );
void win32display_resize_update( void );

void blit( void );

/*
 * Keyboard routines (win32keyboard.c)
 */

void win32keyboard_keypress( WPARAM wParam, LPARAM lParam );
void win32keyboard_keyrelease( WPARAM wParam, LPARAM lParam );

/*
 * Mouse routines (win32mouse.c)
 */

void win32mouse_position( LPARAM lParam );
void win32mouse_button( int button, int down );

/*
 * General user interface routines (win32ui.c)
 */

int win32ui_confirm( const char *string );

int win32ui_picture( const char *filename, int border );

void handle_menu( DWORD cmd, HWND okno );

void win32_verror( int is_error );

/*
 * Statusbar routines (statusbar.c)
 */

void win32statusbar_create();
int win32statusbar_set_visibility( int visible );
void win32statusbar_redraw( HWND hWnd, LPARAM lParam );
void win32statusbar_resize( HWND hWnd );

/*
 * Dialog box reset
 */

void win32ui_pokefinder_clear( void );

#endif                          /* #ifndef FUSE_WIN32INTERNALS_H */
