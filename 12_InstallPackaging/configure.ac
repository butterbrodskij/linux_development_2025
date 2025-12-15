#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Guess the number game], [0.0.1], [fake-email@yandex.ru], [guesser])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guesser])
LT_INIT([disable-static])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src/guesser.c])
AC_CONFIG_HEADERS([config.h])
ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC

# Joint pkgconfig library/include tests.
PKG_CHECK_MODULES([CHECK],[check])

# Variable definitions
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])

# Enable/disable things
AC_ARG_ENABLE([gcov],
	      [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
	      [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile 
		 src/Makefile 
		 tests/Makefile
		 po/Makefile.in
		 Doxyfile
		 ])
AC_OUTPUT
