/* gtkdisplay.c: GTK+ routines for dealing with the Speccy screen
   Copyright (c) 2000-2003 Philip Kendall

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

#ifdef UI_GTK		/* Use this file iff we're using GTK+ */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>

#include "display.h"
#include "fuse.h"
#include "gtkui.h"
#include "screenshot.h"
#include "ui/ui.h"
#include "ui/uidisplay.h"
#include "ui/scaler/scaler.h"
#include "scld.h"

GdkGC *gtkdisplay_gc = NULL;

unsigned long gtkdisplay_colours[16];

/* The size of a 1x1 image in units of
   DISPLAY_ASPECT WIDTH x DISPLAY_SCREEN_HEIGHT */
int image_scale;

/* The height and width of a 1x1 image in pixels */
int image_width, image_height;

/* An RGB image of the Spectrum screen */
static guchar rgb_image[DISPLAY_SCREEN_HEIGHT * DISPLAY_SCREEN_WIDTH * 4];
static const gint rgb_pitch = DISPLAY_SCREEN_WIDTH * 4;

/* The scaled image */
static guchar scaled_image[4 * 2 * DISPLAY_SCREEN_HEIGHT *
			       2 * DISPLAY_SCREEN_WIDTH    ];
static const ptrdiff_t scaled_pitch = 4 * 2 * DISPLAY_SCREEN_WIDTH;

/* The colour palette */
static guchar rgb_colours[16][3] = {

  {   0,   0,   0 },
  {   0,   0, 192 },
  { 192,   0,   0 },
  { 192,   0, 192 },
  {   0, 192,   0 },
  {   0, 192, 192 },
  { 192, 192,   0 },
  { 192, 192, 192 },
  {   0,   0,   0 },
  {   0,   0, 255 },
  { 255,   0,   0 },
  { 255,   0, 255 },
  {   0, 255,   0 },
  {   0, 255, 255 },
  { 255, 255,   0 },
  { 255, 255, 255 },

};

/* And the colours 32-bit format */
static DWORD colours[16];

/* The current size of the window (in units of DISPLAY_SCREEN_*) */
static int gtkdisplay_current_size=1;

static int init_colours( void );
static void gtkdisplay_area(int x, int y, int width, int height);
static int gtkdisplay_configure_notify( int width );
static int register_scalers( void );

/* Callbacks */

static gint gtkdisplay_expose(GtkWidget *widget, GdkEvent *event,
			      gpointer data);
static gint gtkdisplay_configure(GtkWidget *widget, GdkEvent *event,
				 gpointer data);

int
gtkdisplay_init( void )
{
  int x, y, get_width, get_height, depth, error;
  GdkGCValues gc_values;

  gtk_signal_connect( GTK_OBJECT(gtkui_drawing_area), "expose_event", 
		      GTK_SIGNAL_FUNC(gtkdisplay_expose), NULL);
  gtk_signal_connect( GTK_OBJECT(gtkui_drawing_area), "configure_event", 
		      GTK_SIGNAL_FUNC(gtkdisplay_configure), NULL);

  gdk_window_get_geometry( gtkui_drawing_area->window, &x, &y,
			   &get_width, &get_height, &depth );
  gtkdisplay_gc =
    gtk_gc_get( depth, gdk_rgb_get_cmap(), &gc_values, (GdkGCValuesMask) 0 );

  error = init_colours(); if( error ) return error;

  display_ui_initialised = 1;

  return 0;
}

static int
init_colours( void )
{
  size_t i; int error;

  error = scaler_select_bitformat( 888 ); if( error ) return error;

  for( i = 0; i < 16; i++ ) {

#ifdef WORDS_BIGENDIAN
    colours[i] = rgb_colours[i][0] << 24 |
                 rgb_colours[i][1] << 16 |
                 rgb_colours[i][2] <<  8 ;
#else				/* #ifdef WORDS_BIGENDIAN */
    colours[i] = rgb_colours[i][0]       |
		 rgb_colours[i][1] <<  8 |
                 rgb_colours[i][2] << 16 ;
#endif				/* #ifdef WORDS_BIGENDIAN */

  }

  return 0;
}

int
uidisplay_init( int width, int height )
{
  int error;

  image_width = width; image_height = height;
  image_scale = width / DISPLAY_ASPECT_WIDTH;

  error = register_scalers(); if( error ) return error;

  display_refresh_all();

  return 0;
}

static int gtkdisplay_configure_notify( int width )
{
  int size, error;

  size = width / DISPLAY_ASPECT_WIDTH;

  /* If we're the same size as before, nothing special needed */
  if( size == gtkdisplay_current_size ) return 0;

  /* Else set ourselves to the new height */
  gtkdisplay_current_size=size;
  gtk_drawing_area_size( GTK_DRAWING_AREA(gtkui_drawing_area),
			 size * DISPLAY_ASPECT_WIDTH,
			 size * DISPLAY_SCREEN_HEIGHT );

  error = register_scalers(); if( error ) return error;

  /* Redraw the entire screen... */
  display_refresh_all();

  return 0;
}

static int
register_scalers( void )
{
  scaler_register_clear();

  switch( gtkdisplay_current_size ) {

  case 1:

    switch( image_scale ) {
    case 1:
      scaler_register( GFX_NORMAL );
      scaler_select_scaler( GFX_NORMAL );
      return 0;
    case 2:
      scaler_register( GFX_HALF );
      scaler_select_scaler( GFX_HALF );
      return 0;
    }

  case 2:

    switch( image_scale ) {
    case 1:
      scaler_register( GFX_DOUBLESIZE );
      scaler_register( GFX_TV2X );
      scaler_select_scaler( GFX_DOUBLESIZE );
      return 0;
    case 2:
      scaler_register( GFX_NORMAL );
      scaler_select_scaler( GFX_NORMAL );
      return 0;
    }

  }

  ui_error( UI_ERROR_ERROR, "Unknown display size/image size %d/%d",
	    gtkdisplay_current_size, image_scale );
  return 1;
}

void
uidisplay_frame_end( void ) 
{
  return;
}

void
uidisplay_area( int x, int y, int w, int h )
{
  float scale = (float)gtkdisplay_current_size / image_scale;
  int scaled_x, scaled_y, xx, yy;

  if( scaler_flags ) {

    /* Extend the dirty region by 1 pixel for scalers
       that "smear" the screen, e.g. 2xSAI */
    if( scaler_flags & SCALER_EXPAND_1_PIXEL ) {
      x--;
      y--;
      w += 2;   
      h += 2;
    } else if ( scaler_flags & SCALER_EXPAND_2_Y_PIXELS ) {
      y -= 2;
      h += 4;
    }

    /* clip */
    if ( x < 0 ) { w += x; x=0; }
    if ( y < 0 ) { h += y; y=0; }
    if ( w > image_width - x ) w = image_width - x;
    if ( h > image_height - y ) h = image_height - y;
  }

  scaled_x = scale * x; scaled_y = scale * y;

  /* Create the RGB image */
  for( xx = x; xx < x + w; xx++ )
    for( yy = y; yy < y + h; yy++ )
      *(DWORD*)(rgb_image + yy * rgb_pitch + 4 * xx) =
	colours[ display_image[yy][xx] ];

  /* Create scaled image */
  scaler_proc( (BYTE*)&rgb_image[ y * rgb_pitch + 4 * x ], rgb_pitch, NULL, 
	       (BYTE*)&scaled_image[ scaled_y * scaled_pitch + 4 * scaled_x ],
	       scaled_pitch, w, h );

  w *= scale; h *= scale;

  /* Blit to the real screen */
  gtkdisplay_area( scaled_x, scaled_y, w, h );
}

static void gtkdisplay_area(int x, int y, int width, int height)
{
  gdk_draw_rgb_32_image( gtkui_drawing_area->window,
			 gtkui_drawing_area->style->fg_gc[GTK_STATE_NORMAL],
			 x, y, width, height, GDK_RGB_DITHER_NONE,
			 &scaled_image[ y * scaled_pitch + 4 * x ],
			 scaled_pitch );
}

void
uidisplay_hotswap_gfx_mode( void )
{
  fuse_emulation_pause();

  /* Redraw the entire screen... */
  display_refresh_all();

  fuse_emulation_unpause();
}

int
uidisplay_end( void )
{
  return 0;
}

int
gtkdisplay_end( void )
{
  /* Free the allocated GC */
  gtk_gc_release( gtkdisplay_gc );

  return 0;
}

/* Callbacks */

/* Called by gtkui_drawing_area on "expose_event" */
static gint
gtkdisplay_expose( GtkWidget *widget GCC_UNUSED, GdkEvent *event,
		   gpointer data GCC_UNUSED )
{
  gtkdisplay_area(event->expose.area.x, event->expose.area.y,
		  event->expose.area.width, event->expose.area.height);
  return TRUE;
}

/* Called by gtkui_drawing_area on "configure_event" */
static gint
gtkdisplay_configure( GtkWidget *widget GCC_UNUSED, GdkEvent *event,
		      gpointer data GCC_UNUSED )
{
  gtkdisplay_configure_notify( event->configure.width );
  return FALSE;
}

#endif			/* #ifdef UI_GTK */
