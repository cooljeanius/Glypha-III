## automake Makefile for Glypha-III sources

ACLOCAL_AMFLAGS = -I m4 --install

AUTOMAKE_OPTIONS = 1.11 foreign dejagnu

all: xcode

xcode: ../@PACKAGE_NAME@.xcodeproj
	cd .. && @XCODEBUILD@

check_PROGRAMS = SysBeepTest

SysBeepTest_SOURCES = SysBeepTest.c

clean-local:
	-rm -rf *.dSYM || rmdir *.dSYM

DISTCLEANFILES = *~ autoscan.log .DS_Store

distclean-local:
	-rm -rf autom4te.cache || rmdir autom4te.cache

