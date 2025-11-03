#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([hasher-repl], [0.01], [fake-email@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([Rhash is required])])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

# Options
AC_ARG_WITH([readline],
	    [AS_HELP_STRING([--with-readline],
			    [enable experimental support for readline])],
			    [],
			    [with_readline=no])
AS_IF([test "x$with_readline" = xyes],
      [AC_CHECK_LIB([readline], [readline],
		    [AC_SUBST([LIBREADLINE], ["-lreadline"])
		    AC_DEFINE([USE_READLINE], [1], [Use readline library])
		    ], 
		    [AC_MSG_ERROR([--with-readline was given, but test for readline failed])])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
