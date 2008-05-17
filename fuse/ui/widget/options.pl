#!/usr/bin/perl -w

# options.pl: generate options dialog boxes
# Copyright (c) 2001-2004 Philip Kendall

# $Id$

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

# Author contact information:

# E-mail: philip-fuse@shadowmagic.org.uk

use strict;

use lib '../perl';

use Fuse;
use Fuse::Dialog;

die "No data file specified" unless @ARGV;

my @dialogs = Fuse::Dialog::read( shift @ARGV );

print Fuse::GPL( 'options.c: options dialog boxes',
		 '2001-2004 Philip Kendall' ) . << "CODE";

/* This file is autogenerated from options.dat by options.pl.
   Do not edit unless you know what you\'re doing! */

#include <config.h>

#ifdef USE_WIDGET

#include <stdio.h>
#include <string.h>

#include "display.h"
#include "fuse.h"
#include "options.h"
#include "periph.h"
#include "widget_standard.h"
#include "widget_internals.h"
#include "ui/uidisplay.h"

/* General functions used by the options dialogs */
settings_info widget_options_settings;
int widget_options_print_option( int number, const char* string, int value );
int widget_options_print_value( int number, int value );
int widget_options_print_entry( int number, const char *prefix, int value,
				const char *suffix );

static int widget_options_print_label( int number, const char *string );
static int widget_options_print_data( int number, const char *string );

int widget_options_print_option( int number, const char* string, int value )
{
  widget_options_print_label( number, string );
  widget_options_print_value( number, value );
  return 0;
}

static int widget_options_print_label( int number, const char *string )
{
  char buffer[128];
  size_t l, w;

  snprintf( buffer, sizeof( buffer ), "%s", string );
  l = strlen( buffer );

  if( l >= sizeof( buffer ) )
    l = sizeof( buffer ) - 1;
  while( ( w = widget_substringwidth( string, l ) ) >= 224 )
    --l;
  buffer[l] = '\\0';
  w = widget_printstring( 17, number*8+28, WIDGET_COLOUR_FOREGROUND, buffer )
      - 1;
  while ((w += 3) < 240)
    widget_putpixel (w, number*8+35, 0);
  return 0;
}

int widget_options_print_value( int number, int value )
{
  widget_rectangle( 233, number * 8 + 28, 7, 8, WIDGET_COLOUR_BACKGROUND );
  widget_print_checkbox( 233, number * 8 + 28, value );
  widget_display_rasters( number * 8 + 28, 8 );
  return 0;
}

static int widget_options_print_data( int number, const char *string )
{
  size_t width = widget_stringwidth( string );
  widget_rectangle( 240 - width - 2, number * 8 + 28, width + 2, 8,
  		    WIDGET_COLOUR_BACKGROUND );
  widget_printstring( 240 - width, number * 8 + 28,
		      WIDGET_COLOUR_FOREGROUND, string );
  widget_display_rasters( number * 8 + 28, 8 );

  return 0;
}

int
widget_options_print_entry( int number, const char *prefix, int value,
			    const char *suffix )
{
  char buffer[128];
  widget_options_print_label( number, prefix );
  snprintf( buffer, sizeof( buffer ), "%d %s", value, suffix );
  return widget_options_print_data( number, buffer );
}

int widget_options_finish( widget_finish_state finished )
{
  int error;

  /* If we exited normally, actually set the options */
  if( finished == WIDGET_FINISHED_OK ) {
    error = settings_copy( &settings_current, &widget_options_settings );
    settings_free( &widget_options_settings );
    memset( &widget_options_settings, 0, sizeof( settings_info ) );
    if( error ) return error;

    /* Bring the peripherals list into sync with the new options */
    periph_update();
    /* make the needed UI changes */
    uidisplay_hotswap_gfx_mode();
  }

  return 0;
}

CODE

foreach( @dialogs ) { 

    my $count = @{ $_->{widgets} };

    print << "CODE";
static int widget_$_->{name}_show_all( settings_info *show );

int widget_$_->{name}_draw( void *data GCC_UNUSED )
{
  int error;
  
  /* Get a copy of the current settings */
  error = settings_copy( &widget_options_settings, &settings_current );
  if( error ) { settings_free( &widget_options_settings ); return error; }

  /* Draw the dialog box */
  widget_dialog_with_border( 1, 2, 30, 2 + $count );
  error = widget_$_->{name}_show_all( &widget_options_settings );
  if( error ) { settings_free( &widget_options_settings ); return error; }

  widget_display_lines( 2, 2 + $count );

  return 0;
}

static int widget_$_->{name}_show_all( settings_info *show )
\{
  int error;

CODE

    print "  widget_print_title( 16, WIDGET_COLOUR_FOREGROUND, \"$_->{title}\" );\n\n";

    my $which = 0;
    foreach my $widget ( @{ $_->{widgets} } ) {

	$widget->{text} =~ s/\((.)\)/\\012$1\\011/;

	if( $widget->{type} eq "Checkbox" ) {

	    print << "CODE";
  error = widget_options_print_option( $which, "$widget->{text}",
				       show->$widget->{value} );
  if( error ) return error;

CODE
	} elsif( $widget->{type} eq "Entry" ) {

	    print << "CODE";
  error = widget_options_print_entry( $which, "$widget->{text}",
				      show->$widget->{value},
				      "$widget->{data2}" );
  if( error ) return error;
CODE
	} else {
	    die "Unknown type `$widget->{type}'";
	}

        $which++;
    }
        
    print << "CODE";
  return 0;
\}

void
widget_$_->{name}_keyhandler( input_key key )
\{
  int error;
  widget_text_t text_data;

  text_data = text_data;	/* Keep gcc happy */

  switch( key ) \{

#if 0
  case INPUT_KEY_Resize:	/* Fake keypress used on window resize */
    widget_dialog_with_border( 1, 2, 30, 2 + $count );
    widget_$_->{name}_show_all( &widget_options_settings );
    break;
#endif
    
  case INPUT_KEY_Escape:
    widget_end_widget( WIDGET_FINISHED_CANCEL );
    break;

CODE

    $which = 0;
    foreach my $widget ( @{ $_->{widgets} } ) {

	if( $widget->{type} eq "Checkbox" ) {

	    print << "CODE";
  case $widget->{key}:
    widget_options_settings.$widget->{value} = ! widget_options_settings.$widget->{value};
    error = widget_options_print_value( $which, widget_options_settings.$widget->{value} );
    if( error ) return;
    break;

CODE
	} elsif( $widget->{type} eq "Entry" ) {

	    my $title = $widget->{text};

	    $title =~ s/\\01[12]//g;

	    print << "CODE";
  case $widget->{key}:
    text_data.title = "$title";
    text_data.allow = WIDGET_INPUT_DIGIT;
    snprintf( text_data.text, 40, "%d",
	      widget_options_settings.$widget->{value} );
    error = widget_do( WIDGET_TYPE_TEXT, &text_data ); if( error ) return;
    if( widget_text_text ) {
      widget_options_settings.$widget->{value} = atoi( widget_text_text );
      error = widget_options_print_entry(
        $which, "$widget->{text}",
	widget_options_settings.$widget->{value}, "$widget->{data2}"
      );
    }
	    
    break;

CODE
	} else {
	    die "Unknown type `$widget->{type}'";
	}

	$which++;
    }

    print "  case INPUT_KEY_Return:\n";
    print << "CODE";
    widget_end_all( WIDGET_FINISHED_OK );
CODE
    print "    $_->{posthook}();\n" if $_->{posthook};
    print << "CODE";
    display_refresh_all();
    break;

  default:	/* Keep gcc happy */
    break;

  \}
\}
CODE

}

print "\n#endif				/* #ifdef USE_WIDGET */\n";

