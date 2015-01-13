dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Glypha],[III],[/dev/null])
AC_CONFIG_SRCDIR([Enemy.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([1.11 foreign dejagnu dist-bzip2 dist-zip])
AM_MAINTAINER_MODE
EBG_DEVELOPER_DIR

# Checks for programs.
AC_LANG([C])dnl
AC_MSG_CHECKING([for some programs...])
AC_MSG_RESULT([... .. . ])
AM_PROG_CC_C_O
AC_PROG_OBJC
XORG_PROG_RAWCPP
XORG_LD_WRAP
AC_PROG_GCC_TRADITIONAL
AC_BAKEFILE_PROG_MWCC
AC_BAKEFILE_PROG_MWCXX
AC_BAKEFILE_METROWERKS_EXTO
AX_COMPILER_VENDOR

AC_PATH_PROG([XCODEBUILD],[xcodebuild],
             [AC_MSG_ERROR([xcodebuild is required to build.])])dnl

# ResourceManager-related tools:
AC_PATH_PROG([RESMERGER],[ResMerger])dnl
AC_PATH_PROG([REZ],[Rez])dnl
AC_PATH_PROG([DEREZ],[DeRez])dnl
AC_PATH_PROG([REZDET],[RezDet])dnl
AC_PATH_PROG([REZWACK],[RezWack])dnl
AC_PATH_PROG([UNREZWACK],[UnRezWack])dnl
AC_BAKEFILE_RES_COMPILERS

# Other Mac-specific tools:
AC_PATH_PROG([BUILD_STRINGS],[BuildStrings])dnl
AC_PATH_PROG([LD_CLASSIC],[ld_classic])dnl
AC_PATH_PROG([MERGE_PEF],[MergePef])dnl
AC_PATH_PROG([PBXCP],[pbxcp])dnl
AC_PATH_PROG([SPLIT_FORK],[SplitForks])dnl

# Checks for libraries.
AC_MSG_CHECKING([for libraries...])
AC_MSG_RESULT([... .. . ])

if test "x${acl_cv_wl}" = "x"; then
  test -z "${acl_cv_wl}" && export acl_cv_wl='-Wl,'
fi
AC_SUBST([acl_cv_wl])dnl

AC_MSG_CHECKING([for linker flag to verify linked libraries have the correct architecture])
pre_saved_LDFLAGS="${LDFLAGS}"
LDFLAGS="${LDFLAGS} ${acl_cv_wl}-arch_errors_fatal"
AC_LINK_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
               [LD_ARCHFLAGS="${acl_cv_wl}-arch_errors_fatal"],[])
LDFLAGS="${pre_saved_LDFLAGS}"
if test "x${LD_ARCHFLAGS}" != "x"; then
  test -n "${LD_ARCHFLAGS}"
  AC_MSG_RESULT([${LD_ARCHFLAGS}])
  AC_SUBST([LD_ARCHFLAGS])dnl
  ## that should be all we need to do with them for now...
else
  test -z "${LD_ARCHFLAGS}"
  AC_MSG_RESULT([none])
fi

ARCHLESS_LDFLAGS="${LDFLAGS}"
LDFLAGS="${LDFLAGS} ${LD_ARCHFLAGS}"

AH_TEMPLATE([HAVE_LIBSTDC__],
            [Define to 1 if you have the `stdc++' library (-lstdc++).])dnl
AC_CHECK_LIB([stdc++],[main],[
  # this check produces no warning in this case:
  AC_CHECK_LIB([stdc++-static],[main])dnl
],[
  AC_CHECK_LIB([stdc++-static],[main],[
    ## reset early:
    LDFLAGS="${ARCHLESS_LDFLAGS}"
    AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-static],[
      export STATIC_LDFLAGS="${acl_cv_wl}-static"
    ],[
      AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-static-libgcc],[
        export STATIC_LDFLAGS="${acl_cv_wl}-static-libgcc"
      ],[
        AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-static-libstdc++],[
          export STATIC_LDFLAGS="${acl_cv_wl}-static-libstdc++"
        ])dnl
      ])dnl
    ])dnl
    AC_SUBST([STATIC_LDFLAGS])dnl
  ],[
    AC_MSG_WARN([cannot link against libstdc++, static or otherwise])
  ])dnl
])dnl
  ## reset for rest of cases:
LDFLAGS="${ARCHLESS_LDFLAGS}"

# Checks for header files.
AC_MSG_CHECKING([for some headers...])
AC_MSG_RESULT([... .. . ])
AC_BAKEFILE_PRECOMP_HEADERS
AC_BAKEFILE_CREATE_FILE_BK_MAKE_PCH
AC_C_PROTOTYPES
AC_HEADER_STDBOOL
# save these:
my_saved_CFLAGS="${CFLAGS}"
AH_TEMPLATE([HAVE_CARBON_CARBON_H],
           [Define to 1 if you have the <Carbon/Carbon.h> header file.])dnl
AH_TEMPLATE([HAVE_CARBON_H],
            [Define to 1 if you have the <Carbon.h> header file.])dnl
AC_CHECK_HEADER([Carbon.h],[],[
  AC_CHECK_HEADER([Carbon/Carbon.h],[
    AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-framework ${acl_cv_wl}Carbon],
      [export CARBON_CFLAGS="${acl_cv_wl}-framework ${acl_cv_wl}Carbon"
       export CFLAGS="${CFLAGS} ${CARBON_CFLAGS}"
       export LDFLAGS="${LDFLAGS} -framework Carbon"],
      [AC_MSG_WARN([Carbon header is available framework-style, but flag for using Carbon framework fails to work])])
  ],[
    ## needs to be an error because we assume we have the header later:
    AC_MSG_ERROR([cannot find main header for Carbon])
  ])dnl
])dnl
AC_SUBST([CARBON_CFLAGS])dnl
dnl# some Carbon stuff is actually under ApplicationServices:
AC_CHECK_HEADER([ApplicationServices.h],[],[
  AC_CHECK_HEADER([ApplicationServices/ApplicationServices.h],[
    AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-framework ${acl_cv_wl}ApplicationServices],
      [export APP_SERVICES_CFLAGS="${acl_cv_wl}-framework ${acl_cv_wl}ApplicationServices"
       export CFLAGS="${CFLAGS} ${APP_SERVICES_CFLAGS}"
       export LDFLAGS="${LDFLAGS} -framework ApplicationServices"],
      [AC_MSG_WARN([ApplicationServices header is available framework-style, but flag for using ApplicationServices framework fails to work])])
  ],[
    AC_MSG_WARN([cannot find main header for ApplicationServices])
  ])dnl
])dnl
AC_SUBST([APP_SERVICES_CFLAGS])dnl
dnl# likewise with CoreServices:
AC_CHECK_HEADER([CoreServices.h],[],[
  AC_CHECK_HEADER([CoreServices/CoreServices.h],[
    AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-framework ${acl_cv_wl}CoreServices],
      [export CORE_SERVICES_CFLAGS="${acl_cv_wl}-framework ${acl_cv_wl}CoreServices"
       export CFLAGS="${CFLAGS} ${CORE_SERVICES_CFLAGS}"
       export LDFLAGS="${LDFLAGS} -framework CoreServices"],
      [AC_MSG_WARN([CoreServices header is available framework-style, but flag for using CoreServices framework fails to work])])
  ],[
    AC_MSG_WARN([cannot find main header for CoreServices])
  ])dnl
])dnl
AC_SUBST([CORE_SERVICES_CFLAGS])dnl
dnl# ...and, depending on system, AudioToolbox:
AC_CHECK_HEADER([AudioToolbox.h],[],[
  AC_CHECK_HEADER([AudioToolbox/AudioToolbox.h],[
    AX_CHECK_COMPILE_FLAG([${acl_cv_wl}-framework ${acl_cv_wl}AudioToolbox],
      [export AUDIO_TOOLBOX_CFLAGS="${acl_cv_wl}-framework ${acl_cv_wl}AudioToolbox"
       export CFLAGS="${CFLAGS} ${AUDIO_TOOLBOX_CFLAGS}"
       export LDFLAGS="${LDFLAGS} -framework AudioToolbox"],
      [AC_MSG_WARN([AudioToolbox header is available framework-style, but flag for using AudioToolbox framework fails to work])])
  ],[
    AC_MSG_WARN([cannot find main header for AudioToolbox])
  ])dnl
])dnl
AC_SUBST([AUDIO_TOOLBOX_CFLAGS])dnl
AX_CHECK_COMPILE_FLAG([-Wdeprecated-declarations],
                      [CFLAGS="${CFLAGS} -Wdeprecated-declarations"])
AC_CHECK_HEADERS([AudioToolbox/AudioServices.h CarbonCore/Files.h \
                  CarbonCore/MacMemory.h CarbonCore/OSUtils.h \
                  CarbonCore/TextUtils.h CarbonSound/Sound.h \
                  HIToolbox/Events.h HIToolbox/MacWindows.h \
                  HIToolbox/Menus.h QD/QuickdrawAPI.h],[],[],[[
/* taken from Externs.h */
#if !defined(__MWERKS__) || defined(HAVE_CARBON_CARBON_H)# include <Carbon/Carbon.h>#else# if defined(__MWERKS__) || defined(HAVE_CARBON_H)#  include <Carbon.h># else#  error "cannot figure out how to include proper Carbon umbrella header."# endif /* __MWERKS__ || HAVE_CARBON_H */#endif /* !__MWERKS__ || HAVE_CARBON_CARBON_H */
]])dnl

# always reset:
CFLAGS="${my_saved_CFLAGS}"
AC_CHECK_HEADERS([stdio.h])dnl

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([for typedefs, structs, and compiler characteristics...])
AC_MSG_RESULT([... .. . ])
AC_C_BIGENDIAN
AC_C_CONST
AC_C_VOLATILE
XORG_MEMORY_CHECK_FLAGS
XORG_CHECK_MALLOC_ZERO
XORG_CWARNFLAGS
AX_GCC_ARCHFLAG

#FIXME: This check will (sometimes) say that the compiler does not
# support the -fpascal-strings flag, even when it does actually support it:
AX_CHECK_COMPILE_FLAG([-fpascal-strings],
                      [export CFLAGS="${CFLAGS} -fpascal-strings"],
                      [AC_MSG_WARN([this project uses pascal strings but your compiler does not appear to support them])])dnl

CFLAGS_SAVED_AGAIN="${CFLAGS}"
## make sure bad warning flags are rejected:
CFLAGS="${CFLAGS} -Werror"
AX_CHECK_COMPILE_FLAG([-Wno-four-char-constants],
                      [export APPLE_CFLAGS="-Wno-four-char-constants"
                       export CFLAGS="${CFLAGS} ${APPLE_CFLAGS}"],
                      [AX_CHECK_COMPILE_FLAG([-Wno-multichar],
                            [export APPLE_CFLAGS="-Wno-multichar"
                             export CFLAGS="${CFLAGS} ${APPLE_CFLAGS}"])dnl
                      ])dnl
AC_SUBST([APPLE_CFLAGS])dnl
  ## reset to safe ones:
CFLAGS="${CFLAGS_SAVED_AGAIN}"

# Checks for library functions.
AC_MSG_CHECKING([for some functions...])
AC_MSG_RESULT([... .. . ])
AC_FUNC_MALLOC
AC_CHECK_FUNCS([CopyPascalStringToC p2cstr sleep getenv])dnl

# Output.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
