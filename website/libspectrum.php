<?php

/* libspectrum.php: the libspectrum 'home' page
   Copyright (c) 1999-2003 Darren Salt, Philip Kendall

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

include ".inc/fuse.inc";

fuse_title ("libspectrum - emulator support library");
fuse_menu_heading ("libspectrum");

#<!-- ======================================================= -->

fuse_section (NULL, "What is it?", <<<END_SECTION
  <p>libspectrum is a library designed to make the input and output of some ZX Spectrum emulator files slightly easier. It is intended to be usable on Unix variants, Win32 and Mac OS X. Currently, it is mainly (only?) used by <a href="fuse.php">Fuse</a>, but other Spectrum emulator and utility authors are encouraged to use it.</p>

END_SECTION
);

#<!-- ======================================================= -->

fuse_section ("Supported formats", "Which formats does it support?", <<<END_SECTION
  <ul>
   <li>Snapshots:
    <ul>
     <li>read/write: .z80, .szx, .sna</li>
     <li>read only: .zxs, .sp., .snp, +D snapshots</li>
    </ul>
   </li>
   <li>Tape images:
    <ul>
     <li>read/write: .tzx, .tap</li>
     <li>read only: Warajevo .tap</li>
    </ul>
   </li>
   <li>Input recordings:
    <ul><li>read/write: .rzx</li></ul>
   </li>
   <li>Timex cartridges:
    <ul><li>read only: .dck</li></ul>
   </li>
  </ul>

  <p>There are also some useful utility routines to do things like identify Spectrum files, or give the timings for various machines. For more details, see the <a href="libspectrum.txt">supplied documentation</a>.</p>

END_SECTION
);

#<!-- ======================================================= -->

fuse_section ("Download", "Downloads", <<<END_SECTION

  <p>libspectrum is licensed under the <a href="COPYING">GNU General Public License</a>. Please read this before downloading libspectrum if you're not already familiar with it.</p>

  <h3>Source</h3>
  <ul>
   <li><a href="http://prdownloads.sourceforge.net/fuse-emulator/libspectrum-0.2.0.1.tar.gz?download">libspectrum-0.2.0.1.tar.gz</a> (<a href="http://prdownloads.sourceforge.net/fuse-emulator/libspectrum-0.2.0.1.tar.gz.sig?download">PGP signature</a>) or from <a href="ftp://ftp.worldofspectrum.org/pub/sinclair/emulators/unix/libspectrum-0.2.0.1.tar.gz">World of Spectrum</a> (<a href="ftp://ftp.worldofspectrum.org/pub/sinclair/emulators/unix/libspectrum-0.2.0.1.tar.gz.sig">signature</a>).</li>
   <li>The source code release above is signed with the <a href="http://wwwkeys.pgp.net:11371/pks/lookup?op=get&amp;search=0xD0767AB9">Fuse Release Key, ID <tt>D0767AB9</tt></a>, which has fingerprint <tt>064E 0BA9 688F
2699 3267 B1E5 1043 EEEB D076 7AB9</tt>. This is different from the key used to sign the 0.1.1 release as I forgot the passphrase for that key <tt>:-(</tt>.</li>
  </ul>

  <h3>Binaries</h3>
  <p>Packages are available for some Unix distributions; in general, any problems which are specific to the packages should be sent to the package maintainer.</p>
  <ul>
   <li><a href="http://www.youmustbejoking.demon.co.uk/progs.stable.html">Debian stable</a> and <a href="http://www.youmustbejoking.demon.co.uk/progs.unstable.html">unstable</a> (both 0.2.0.1) by Darren Salt</li>
   <li><a href="http://www.FreeBSD.org/cgi/cvsweb.cgi/ports/emulators/libspectrum/">FreeBSD</a> (0.2.0.1)</li>
   <li><a href="http://www.gentoo.org/dyn/pkgs/app-emulation/libspectrum.xml">Gentoo</a> (0.1.1)</li>
   <li><a href="http://www.speccy.org/sinclairmania/arch/emu/mandrake/">Mandrake 9.1 and 9.2</a> (0.2.0.1) by Miguel Barrio Orsikowsky</li>
   <li><a href="http://www.netbsd.org/">NetBSD</a> has 0.2.0.1 as <a href="http://cvsweb.netbsd.org/bsdweb.cgi/pkgsrc/emulators/libspectrum/">emulators/libspectrum</a></li>
   <li><a href="http://www.openbsd.org/">OpenBSD</a> users can find a port of v0.1.0 in <a href="http://www.openbsd.org/cgi-bin/cvsweb/ports/devel/libspectrum/">ports/devel/libspectrum</a></li>
   <li><a href="http://www.pld.net.pl/">PLD</a> users have an RPM available</li>
   <li><a href="mailto:spec(at)webtech(dot)pl">Marek Januszewski</a> has made a <a href="libspectrum-0.2.0.1-i386-1spec.tgz">Slackware 9.1</a> (<a href="libspectrum-0.2.0.1-i386-1spec.tgz.md5">md5 sum</a>) package of 0.2.0.1.</li>
  </ul>

END_SECTION
);

#<!-- ======================================================= -->

fuse_section (NULL, "Development", <<<END_SECTION
  <p>If you're interested in working on libspectrum, subscribe to the <a href="http://lists.sourceforge.net/lists/listinfo/fuse-emulator-devel">fuse-emulator-devel</a> mailing list and/or see the <a href="http://sourceforge.net/projects/fuse-emulator/">project page</a> on SourceForge. If you just want news of new versions, you probably want the (low volume) <a href="http://lists.sourceforge.net/lists/listinfo/fuse-emulator-announce">fuse-emulator-announce</a> list instead.</p>

  <p>Finally, the <a href="libspectrum-cvs.tar.gz">latest development version</a> should always be available. Don't expect any support for this, or even that it can be compiled...</p>

END_SECTION
);

#<!-- ======================================================= -->

fuse_related ("Fuse", "fuse.php");

fuse_footer ();
?>
