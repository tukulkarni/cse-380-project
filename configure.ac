#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([CPVEF], [1.0], [tukulkarni@utexas.edu])
AC_CONFIG_SRCDIR([src])
AM_INIT_AUTOMAKE(cpvef,1.0)
AC_CONFIG_FILES([src/Makefile])
AC_OUTPUT(Makefile)
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lcunit':
AC_CHECK_LIB([cunit], [main])
# FIXME: Replace `main' with a function in `-lgrvy':
AC_CHECK_LIB([grvy], [main])
# FIXME: Replace `main' with a function in `-lgsl':
AC_CHECK_LIB([gsl], [main])
# FIXME: Replace `main' with a function in `-lgslcblas':
AC_CHECK_LIB([gslcblas], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp])

AC_OUTPUT
