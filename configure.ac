AC_PREREQ(2.61)
AC_INIT(cpp-active-record, 0.7.0)
AC_CONFIG_SRCDIR([src/active_record.cpp])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([cpp-active-record], [0.7.0])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB


# Checks for libraries.
AC_ARG_WITH([sqlite3], AS_HELP_STRING([--with-sqlite3], [Build with sqlite3-backend support]))
if test "x$with_sqlite3" = "xyes"; then
	PKG_CHECK_MODULES([SQLITE3], [sqlite3 >= 3.11.0])
	CXXFLAGS+=" $SQLITE3_CFLAGS "
	LIBS+=" $SQLITE3_LIBS "
    AM_CONDITIONAL([SQLITE3_BACKEND], [true])
    AC_DEFINE([HAVE_SQLITE3],[1],[Enabled sqlite3])
else
    AM_CONDITIONAL([SQLITE3_BACKEND], [false]) 
fi
AC_ARG_WITH([postgres], AS_HELP_STRING([--with-postgres], [Build with postgres-backend support]))
if test "x$with_postgres" = "xyes"; then
    PKG_CHECK_MODULES([POSTGRES], [libpq >= 9.5.4])
	CXXFLAGS+=" $POSTGRES_CFLAGS "
	LIBS+=" $POSTGRES_LIBS "
    AM_CONDITIONAL([POSTGRES_BACKEND], [true]) 
    AC_DEFINE([HAVE_POSTGRES],[1],[Enabled postgres]) 
else
    AM_CONDITIONAL([POSTGRES_BACKEND], [false]) 
fi

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_LSTAT
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MEMCMP
AC_HEADER_STDC
AC_CHECK_FUNCS([memset strcasecmp])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
