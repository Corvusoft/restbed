AC_PREREQ([2.69])
AC_INIT([restbed], [5.0.0], [https://github.com/Corvusoft/restbed/issues], [restbed], [https://corvusoft.com])
AC_CONFIG_SRCDIR([src/corvusoft/restbed/service.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIRS([m4])

AM_PROG_AR
LT_PREREQ([2.4])
LT_INIT([shared static])

AC_PROG_CXX
AC_LANG([C++])

PKG_PROG_PKG_CONFIG([0.29])

dnl Check for C++23 support
AC_CACHE_CHECK([whether $CXX supports -std=c++23],
    [restbed_cv_cxx23],
    [saved_CXXFLAGS="$CXXFLAGS"
     CXXFLAGS="$CXXFLAGS -std=c++23"
     AC_COMPILE_IFELSE(
         [AC_LANG_PROGRAM([[]])],
         [restbed_cv_cxx23=yes],
         [restbed_cv_cxx23=no])
     CXXFLAGS="$saved_CXXFLAGS"])
AS_IF([test "x$restbed_cv_cxx23" = "xyes"],
    [STD_CXXFLAGS="-std=c++23"],
    [AC_MSG_ERROR([$CXX does not support -std=c++23; GCC 13+ or Clang 17+ is required.])])
AC_SUBST([STD_CXXFLAGS])

dnl Pthreads
AC_MSG_CHECKING([for -pthread compiler/linker flag])
ac_save_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -pthread"
AC_LINK_IFELSE(
    [AC_LANG_PROGRAM([[#include <pthread.h>]], [[pthread_t t; (void)pthread_create(&t,0,0,0);]])],
    [AC_MSG_RESULT([yes])
     PTHREAD_CFLAGS="-pthread"
     PTHREAD_LIBS="-pthread"],
    [AC_MSG_RESULT([no])
     CXXFLAGS="$ac_save_CXXFLAGS"
     AC_CHECK_LIB([pthread], [pthread_create],
         [PTHREAD_CFLAGS=""
          PTHREAD_LIBS="-lpthread"],
         [AC_MSG_ERROR([POSIX threads not found])])])
CXXFLAGS="$ac_save_CXXFLAGS"
AC_SUBST([PTHREAD_CFLAGS])
AC_SUBST([PTHREAD_LIBS])

dnl Build options
AC_ARG_ENABLE([ssl],
    [AS_HELP_STRING([--disable-ssl],
        [disable SSL/TLS support @<:@default: enabled@:>@])],
    [enable_ssl=$enableval], [enable_ssl=yes])

AC_ARG_ENABLE([ipc],
    [AS_HELP_STRING([--enable-ipc],
        [enable Unix domain socket support @<:@default: disabled@:>@])],
    [enable_ipc=$enableval], [enable_ipc=no])

AC_ARG_ENABLE([tests],
    [AS_HELP_STRING([--disable-tests],
        [disable building the test suite @<:@default: enabled@:>@])],
    [enable_tests=$enableval], [enable_tests=yes])

dnl ASIO (standalone, header-only)
ASIO_CFLAGS="-DASIO_STANDALONE=1"
AC_ARG_WITH([asio-include],
    [AS_HELP_STRING([--with-asio-include=DIR], [path to ASIO headers])],
    [ASIO_CFLAGS="$ASIO_CFLAGS -I$withval"])
AC_SUBST([ASIO_CFLAGS])

saved_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $ASIO_CFLAGS"
AC_CHECK_HEADER([asio.hpp], [],
    [AC_MSG_ERROR([ASIO not found. Install libasio-dev or pass --with-asio-include=DIR.])])
CPPFLAGS="$saved_CPPFLAGS"

dnl OpenSSL
OPENSSL_CFLAGS=""
OPENSSL_LIBS=""
OPENSSL_REQUIRES_PRIVATE=""
AS_IF([test "x$enable_ssl" = "xyes"], [
    PKG_CHECK_MODULES([OPENSSL], [openssl],
        [OPENSSL_REQUIRES_PRIVATE="openssl"],
        [AC_MSG_ERROR([OpenSSL not found. Install libssl-dev or pass --disable-ssl.])])
])
AC_SUBST([OPENSSL_CFLAGS])
AC_SUBST([OPENSSL_LIBS])
AC_SUBST([OPENSSL_REQUIRES_PRIVATE])

dnl Catch2 (tests only)
AS_IF([test "x$enable_tests" = "xyes"], [
    PKG_CHECK_MODULES([CATCH2], [catch2 >= 3.0], [],
        [AC_MSG_ERROR([catch2 >= 3.0 not found. Install catch2 or pass --disable-tests.])])
])

dnl Windows (MinGW/Cygwin) host: the public headers switch between
dnl __declspec(dllexport/dllimport) based on WIN_DLL_EXPORT. Only define it
dnl when actually targeting a Windows host; it is meaningless elsewhere.
case "$host_os" in
    mingw*|cygwin*|msys*) build_windows=yes ;;
    *)                    build_windows=no  ;;
esac

AM_CONDITIONAL([BUILD_SSL],     [test "x$enable_ssl"    = "xyes"])
AM_CONDITIONAL([BUILD_IPC],     [test "x$enable_ipc"    = "xyes"])
AM_CONDITIONAL([BUILD_TESTS],   [test "x$enable_tests"  = "xyes"])
AM_CONDITIONAL([BUILD_WINDOWS], [test "x$build_windows" = "xyes"])

AC_CONFIG_FILES([Makefile test/Makefile restbed.pc])
AC_OUTPUT

AS_ECHO(["
##############################################################
#                                                            #
#  Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.  #
#                                                            #
##############################################################

   restbed ${VERSION} configured:
     CXX           : ${CXX}
     SSL support   : ${enable_ssl}
     IPC support   : ${enable_ipc}
     Tests         : ${enable_tests}
"])
