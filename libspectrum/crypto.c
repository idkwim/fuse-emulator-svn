/* crypto.c: crytography-related functions
   Copyright (c) 2002 Philip Kendall

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

#ifdef HAVE_GCRYPT_H

#include <gcrypt.h>

#include "internals.h"

static const char *key_p = "9E140C4CEA9CA011AA8AD17443CB5DC18DC634908474992D38AB7D4A27038CBB209420BA2CAB8508CED35ADF8CBD31A0A034FC082A168A0E190FFC4CCD21706F",
  *key_q = "C52E9CA1804BD021FFAD30E8FB89A94437C2E4CB",
  *key_g = "90E56D9493DE80E1A35F922007357888A1A47805FD365AD27BC5F184601EBC74E44F576AA4BF8C5244D202BBAE697C4F9132DFB7AD0A56892A414C96756BD21A",
  *key_y = "7810A35AC94EA5750934FB9C922351EE597C71E2B83913C121C6655EA25CE7CBE2C259FA3168F8475B2510AA29C5FEB50ACAB25F34366C2FFC93B3870A522232",
  *key_x = "9A4E53CC249750C3194A38A3BE3EDEED28B171A9";

static const char *private_key =
  "(key-data (private-key (dsa (p %m) (q %m) (g %m) (y %m) (x %m))))";

#define HASH_ALGORITHM GCRY_MD_SHA1
#define MPI_COUNT 5

static libspectrum_error get_hash( GcrySexp *hash, libspectrum_byte *data,
				   size_t data_length );
static libspectrum_error create_key( GcrySexp *key );
static void free_mpis( GcryMPI *mpis, size_t n );
static libspectrum_error get_mpis( GcryMPI *r, GcryMPI *s,
				   GcrySexp signature );
static libspectrum_error
serialise_mpis( libspectrum_byte **signature, size_t *signature_length,
		GcryMPI r, GcryMPI s );

static libspectrum_error
restore_mpis( GcryMPI *r, GcryMPI *s, const libspectrum_byte *signature,
	      size_t signature_length );

libspectrum_error
libspectrum_sign_data( libspectrum_byte **signature, size_t *signature_length,
		       libspectrum_byte *data, size_t data_length )
{
  int error;
  GcrySexp hash, key, s_signature;
  GcryMPI r, s;

  error = get_hash( &hash, data, data_length ); if( error ) return error;

  error = create_key( &key );
  if( error ) { gcry_sexp_release( hash ); return error; }

  error = gcry_pk_sign( &s_signature, hash, key );
  if( error ) {
    libspectrum_print_error( "libspectrum_sign_data: error signing data: %s",
			     gcry_strerror( error ) );
    gcry_sexp_release( key ); gcry_sexp_release( hash );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  gcry_sexp_release( key ); gcry_sexp_release( hash );

  error = get_mpis( &r, &s, s_signature );
  if( error ) { gcry_sexp_release( s_signature ); return error; }

  gcry_sexp_release( s_signature );

  error = serialise_mpis( signature, signature_length, r, s );
  if( error ) { gcry_mpi_release( r ); gcry_mpi_release( s ); return error; }

  gcry_mpi_release( r ); gcry_mpi_release( s );

  return LIBSPECTRUM_ERROR_NONE;
}

static libspectrum_error
get_hash( GcrySexp *hash, libspectrum_byte *data, size_t data_length )
{
  int error;
  char *digest; size_t digest_length;
  GcryMPI hash_mpi;
  
  digest_length = gcry_md_get_algo_dlen( HASH_ALGORITHM );
  digest = malloc( digest_length );
  if( !digest ) {
    libspectrum_print_error( "get_hash: out of memory" );
    return LIBSPECTRUM_ERROR_MEMORY;
  }

  gcry_md_hash_buffer( HASH_ALGORITHM, digest, data, data_length );

  error = gcry_mpi_scan( &hash_mpi, GCRYMPI_FMT_USG, digest, &digest_length );
  if( error ) {
    libspectrum_print_error( "get_hash: error creating hash MPI: %s",
			     gcry_strerror( error )
    );
    free( digest );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  free( digest );

  error = gcry_sexp_build( hash, NULL, "(%m)", hash_mpi );
  if( error ) {
    libspectrum_print_error( "get_hash: error creating hash sexp: %s",
			     gcry_strerror( error )
    );
    gcry_mpi_release( hash_mpi );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  gcry_mpi_release( hash_mpi );

  return LIBSPECTRUM_ERROR_NONE;
}

static libspectrum_error
create_key( GcrySexp *key )
{
  int error;
  size_t i;
  GcryMPI mpis[MPI_COUNT];

  for( i=0; i<MPI_COUNT; i++ ) mpis[i] = NULL;

               error = gcry_mpi_scan( &mpis[0], GCRYMPI_FMT_HEX, key_p, NULL );
  if( !error ) error = gcry_mpi_scan( &mpis[1], GCRYMPI_FMT_HEX, key_q, NULL );
  if( !error ) error = gcry_mpi_scan( &mpis[2], GCRYMPI_FMT_HEX, key_g, NULL );
  if( !error ) error = gcry_mpi_scan( &mpis[3], GCRYMPI_FMT_HEX, key_y, NULL );
  if( !error ) error = gcry_mpi_scan( &mpis[4], GCRYMPI_FMT_HEX, key_x, NULL );

  if( error ) {
    libspectrum_print_error( "create_key: error creating MPIs: %s",
			     gcry_strerror( error ) );
    free_mpis( mpis, MPI_COUNT );
    return LIBSPECTRUM_ERROR_LOGIC;
  }
  
  error = gcry_sexp_build( key, NULL, private_key,
			   mpis[0], mpis[1], mpis[2], mpis[3], mpis[4] );
  if( error ) {
    libspectrum_print_error( "create_key: error creating key: %s",
			     gcry_strerror( error ) );
    free_mpis( mpis, MPI_COUNT );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  free_mpis( mpis, MPI_COUNT );

  error = gcry_pk_testkey( *key );
  if( error ) {
    libspectrum_print_error( "create_key: key is invalid: %s",
			     gcry_strerror( error ) );
    gcry_sexp_release( *key );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  return LIBSPECTRUM_ERROR_NONE;
}

static void
free_mpis( GcryMPI *mpis, size_t n )
{
  size_t i;
  for( i=0; i<n; i++ ) if( mpis[i] ) gcry_mpi_release( mpis[i] );
}

static libspectrum_error
get_mpis( GcryMPI *r, GcryMPI *s, GcrySexp signature )
{
  const char *buffer; size_t length;
  size_t i; GcrySexp pair; GcryMPI mpi;

  *r = *s = NULL;

  buffer = gcry_sexp_nth_data( signature, 0, &length );
  if( length != 7 || memcmp( buffer, "sig-val", 7 ) ) {
    libspectrum_print_error( "get_mpis: signature is not a signature" );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  signature = gcry_sexp_nth( signature, 1 );
  if( !signature ) {
    libspectrum_print_error( "get_mpis: signature has no data" );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  buffer = gcry_sexp_nth_data( signature, 0, &length );
  if( length != 3 || memcmp( buffer, "dsa", 3 ) ) {
    libspectrum_print_error( "get_mpis: signature is not a DSA signature" );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  for( i=1;; i++ ) {

    pair = gcry_sexp_nth( signature, i );
    if( !pair ) break;

    buffer = gcry_sexp_nth_data( pair, 0, &length );
    mpi = gcry_sexp_nth_mpi( pair, 1, GCRYMPI_FMT_STD );
    if( length != 1 || !mpi ) {
      if( *r ) gcry_mpi_release( *r ); if( *s ) gcry_mpi_release( *s );
      libspectrum_print_error( "get_mpis: corrupt signature" );
      return LIBSPECTRUM_ERROR_NONE;
    }

    if( *buffer == 'r' ) {
      if( *r != NULL ) {
	libspectrum_print_error( "get_mpis: duplicate 'r'" );
	gcry_mpi_release( *r ); if( *s ) gcry_mpi_release( *s );
	return LIBSPECTRUM_ERROR_LOGIC;
      }
      *r = mpi;
    } else if( *buffer == 's' ) {
      if( *s != NULL ) {
	libspectrum_print_error( "get_mpis: duplicate 's'" );
	if( *r ) gcry_mpi_release( *r ); gcry_mpi_release( *s );
	return LIBSPECTRUM_ERROR_LOGIC;
      }
      *s = mpi;
    } else {
      libspectrum_print_error( "get_mpis: corrupt signature (2)" );
      if( *r ) gcry_mpi_release( *r ); if( *s ) gcry_mpi_release( *s );
      return LIBSPECTRUM_ERROR_LOGIC;
    }
  }

  if( !(*r) || !(*s) ) {
    libspectrum_print_error( "get_mpis: signature not complete" );
    if( *r ) gcry_mpi_release( *r ); if( *s ) gcry_mpi_release( *s );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  return LIBSPECTRUM_ERROR_NONE;
}

static libspectrum_error
serialise_mpis( libspectrum_byte **signature, size_t *signature_length,
		GcryMPI r, GcryMPI s )
{
  int error;
  size_t length, length_s;

  error = gcry_mpi_print( GCRYMPI_FMT_PGP, NULL, &length, r );
  if( error ) {
    libspectrum_print_error( "serialise_mpis: length of r: %s",
			     gcry_strerror( error ) );
    gcry_mpi_release( r ); gcry_mpi_release( s );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  error = gcry_mpi_print( GCRYMPI_FMT_PGP, NULL, &length_s, s );
  if( error ) {
    libspectrum_print_error( "serialise_mpis: length of s: %s",
			     gcry_strerror( error ) );
    gcry_mpi_release( r ); gcry_mpi_release( s );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  length += length_s; *signature_length = length;

  *signature = malloc( length );
  if( signature == NULL ) {
    libspectrum_print_error( "serialise_mpis: out of memory" );
    gcry_mpi_release( r ); gcry_mpi_release( s );
    return LIBSPECTRUM_ERROR_MEMORY;
  }

  error = gcry_mpi_print( GCRYMPI_FMT_PGP, *signature, &length, r );
  if( error ) {
    libspectrum_print_error( "serialise_mpis: printing r: %s",
			     gcry_strerror( error ) );
    free( *signature );
    gcry_mpi_release( r ); gcry_mpi_release( s );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  length = *signature_length - length;
  error = gcry_mpi_print( GCRYMPI_FMT_PGP, *signature + length, &length, s );
  if( error ) {
    libspectrum_print_error( "serialise_mpis: printing s: %s",
			     gcry_strerror( error ) );
    free( *signature );
    gcry_mpi_release( r ); gcry_mpi_release( s );
    return LIBSPECTRUM_ERROR_LOGIC;
  }

  return LIBSPECTRUM_ERROR_NONE;
}

libspectrum_error
libspectrum_verify_signature( const libspectrum_byte *signature,
			      size_t signature_length,
			      const libspectrum_byte *data, size_t length )
{
  libspectrum_error error;
  GcryMPI r, s;

  error = restore_mpis( &r, &s, signature, signature_length );
  if( error ) return error;

  return LIBSPECTRUM_ERROR_NONE;
}

static libspectrum_error
restore_mpis( GcryMPI *r, GcryMPI *s, const libspectrum_byte *signature,
	      size_t signature_length )
{
  size_t length; int error;

  length = signature_length;
  error = gcry_mpi_scan( r, GCRYMPI_FMT_PGP, signature, &length );
  if( error ) {
    libspectrum_print_error( "restore_mpis: reading r: %s",
			     gcry_strerror( error ) );
    return LIBSPECTRUM_ERROR_CORRUPT;
  }

  length = signature_length - length;
  error = gcry_mpi_scan( s, GCRYMPI_FMT_PGP, signature + length, &length );
  if( error ) {
    libspectrum_print_error( "restore_mpis: reading s: %s",
			     gcry_strerror( error ) );
    gcry_mpi_release( *r );
    return LIBSPECTRUM_ERROR_CORRUPT;
  }

  return LIBSPECTRUM_ERROR_NONE;
}

#endif				/* #ifdef HAVE_GCRYPT_H */
