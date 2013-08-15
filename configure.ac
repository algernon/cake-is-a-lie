AC_PREREQ([2.69])
AC_INIT([cake-is-a-lie], [20], [algernon@debian.org])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([src/cake-is-a-lie.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_PROG_CC_C_O

# Checks for libraries.
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES(caca, caca,,)
PKG_CHECK_MODULES(imlib2, imlib2,,)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
