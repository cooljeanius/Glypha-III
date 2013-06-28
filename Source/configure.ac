#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([Glypha], [III])
AC_CONFIG_SRCDIR([Enemy.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([1.11 foreign])
AM_MAINTAINER_MODE
EBG_DEVELOPER_DIR

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_GCC_TRADITIONAL
AC_BAKEFILE_PROG_MWCC
AC_BAKEFILE_PROG_MWCXX
AX_COMPILER_VENDOR

AC_PATH_PROG([XCODEBUILD], [xcodebuild], [AC_MSG_ERROR([xcodebuild is required to build.])])

# ResourceManager-related tools
AC_PATH_PROG([RESMERGER], [ResMerger])
AC_PATH_PROG([REZ], [Rez])
AC_PATH_PROG([DEREZ], [DeRez])
AC_PATH_PROG([REZDET], [RezDet])
AC_PATH_PROG([REZWACK], [RezWack])
AC_PATH_PROG([UNREZWACK], [UnRezWack])
AC_BAKEFILE_RES_COMPILERS

# Other Mac-specific tools
AC_PATH_PROG([BUILD_STRINGS], [BuildStrings])
AC_PATH_PROG([LD_CLASSIC], [ld_classic])
AC_PATH_PROG([MERGE_PEF], [MergePef])
AC_PATH_PROG([PBXCP], [pbxcp])
AC_PATH_PROG([SPLIT_FORK], [SplitForks])

# Checks for libraries.
AC_CHECK_LIB([stdc++], [main])
AC_CHECK_LIB([stdc++-static], [main])

# Checks for header files.
AC_BAKEFILE_PRECOMP_HEADERS
AC_BAKEFILE_CREATE_FILE_BK_MAKE_PCH
AC_C_PROTOTYPES
AC_HEADER_STDC
AC_CHECK_HEADERS([Carbon.h Carbon/Carbon.h CarbonCore/Files.h CarbonCore/MacMemory.h CarbonCore/OSUtils.h CarbonSound/Sound.h \
                  HIToolbox/Events.h HIToolbox/MacWindows.h HIToolbox/Menus.h QD/QuickdrawAPI.h])
AC_CHECK_HEADERS([stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([sleep])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
