/* keys.c: DSA keys used by various emulators
   Copyright (c) 2003 Philip Kendall

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

#include <libspectrum.h>

#include "utils.h"

struct rzx_key known_keys[] = {

  {
    0x99c65778, "Fuse 0.6.1", {
      "A9E3BD74E136A9ABD41E614383BB1B01EB24B2CD7B920ED6A62F786A879AC8B00F2FF318BF96F81654214B1A064889FF6D8078858ED00CF61D2047B2AAB7888949F35D166A2BBAAE23A331BD4728A736E76901D74B195B68C4A2BBFB9F005E3655BDE8256C279A626E00C7087A2D575F78D7DC5CA6E392A535FFE47A816BA503",
      "FE8D540EED2CAE1983690E2886259F8956FB5A19",
      "9680ABFFB98EF2021945ADDF86C21D6EE3F7C8777FB0A0220AB59E9DFA3A3338611B32CFD1F22F8F26547858754ED93BFBDD87DC13C09F42B42A36B2024467D98EB754DEB2847FCA7FC60C81A99CF95133847EA38AD9D037AFE9DD189E9F0EE47624848CEE840D7E3724A39681E71B97ECF777383DC52A48C0A2C93BADA93F4C",
      "46605F0514D56BC0B4207A350367A5038DBDD4DD62B7C997D26D0ADC5BE42D01F852C199E34553BCBCE5955FF80E3B402B55316606D7E39C0F500AE5EE41A7B7A4DCE78EC19072C21FCC7BA48DFDC830C17B72BCAA2B2D70D9DFC0AAD9B7E73F7AEB6241E54D55C33E41AB749CAAFBE7AB00F2D74C500E5F5DD63BD299C65778",
      ""
    }
  },

  {
    0x0a522232, "Fuse Test Key", {
      "9E140C4CEA9CA011AA8AD17443CB5DC18DC634908474992D38AB7D4A27038CBB209420BA2CAB8508CED35ADF8CBD31A0A034FC082A168A0E190FFC4CCD21706F",
      "C52E9CA1804BD021FFAD30E8FB89A94437C2E4CB",
      "90E56D9493DE80E1A35F922007357888A1A47805FD365AD27BC5F184601EBC74E44F576AA4BF8C5244D202BBAE697C4F9132DFB7AD0A56892A414C96756BD21A",
      "7810A35AC94EA5750934FB9C922351EE597C71E2B83913C121C6655EA25CE7CBE2C259FA3168F8475B2510AA29C5FEB50ACAB25F34366C2FFC93B3870A522232",
      "9A4E53CC249750C3194A38A3BE3EDEED28B171A9"
    }
  },

  {
    0x6db9762e, "Spectaculator", {
      "A0A443B0647EEDA943123AB1AB83E3DB046A77B297D259020AAD1D282228E4DCDE1D9FC57CC66E5CFB314A959C7CDC573D87B5C8F0B205CA8BD3D5096F4BAF3D46C086C2033D56B8A2DEBB46CD2C3FEC1EFA5A496640CE1A3E3E4D43C2207136AD7ED14214C2D969ECA9093FD1981B6F4BAAA03ED50177A1E8B3B316ABFC21E3",
      "BD59B71AD3DFEDD855CAA88A66026848C974E6FF",
      "7D4F89B98D2C75AB8062BAD686FAB046B5645090402B5E67EA6E006BD0C26DC8D6E01052B2FBBCC39EE1920B00E61AD32DF8107A37A379E647B58B0FA523737EF9F96AB09C678792AEE2F525439B65A3CE4D567A532C4DF532C1F096AE6B07B9E24CFE9AC83DEA38598B2777753814599AC5ED22D41D642D68824525DDA93602",
      "21B3C0382C9774801335002695DB268603E000405402F31CAFD9D508FB7D5374C1F132CED091BF94F3F6219FB1613CF6F2CD12091D446F9AF4111581C06AA583671C243EE3FDF81953FD1199265BD94B36F9B4EDB915DD19DD1ACD9904F592DF67B74154F88FC4A79E774387AAEDF66B1F9AF33D95739A12B5DD73326DB9762E",
      NULL
    }
  },

  { 0 }				/* End marker */
  
};
