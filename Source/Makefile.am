## automake Makefile for Glypha-III sources

ACLOCAL_AMFLAGS = -I m4 --install

AUTOMAKE_OPTIONS = 1.11.6 foreign dejagnu

all: xcode

xcode: ../@PACKAGE_NAME@.xcodeproj
	cd .. && @XCODEBUILD@

BUILT_SOURCES = config.h

## the configure script should subst both of these for us:
AM_CFLAGS = $(CWARNFLAGS) $(APPLE_CFLAGS)

check_PROGRAMS = SysBeepTest

SysBeepTest_SOURCES = SysBeepTest.c

bin_PROGRAMS = Glypha

Glypha_SOURCES = Enemy.c Graphics.c Interface.c Main.c Play.c Prefs.c \
  SetUpTakeDown.c Sound.c Utilities.c
Glypha_CFLAGS = $(CWARNFLAGS) -m32 -mmacosx-version-min=10.4
Glypha_DEPENDENCIES = config.h Externs.h

clean-local:
	-rm -rf *.dSYM || rmdir *.dSYM

DISTCLEANFILES = *~ autoscan.log .DS_Store

distclean-local:
	-rm -rf autom4te.cache || rmdir autom4te.cache

