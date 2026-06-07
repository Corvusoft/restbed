ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = librestbed.la

librestbed_la_SOURCES = \
    src/corvusoft/restbed/request.cpp \
    src/corvusoft/restbed/resource.cpp \
    src/corvusoft/restbed/response.cpp \
    src/corvusoft/restbed/service.cpp \
    src/corvusoft/restbed/session.cpp \
    src/corvusoft/restbed/settings.cpp \
    src/corvusoft/restbed/ssl_settings.cpp \
    src/corvusoft/restbed/string.cpp \
    src/corvusoft/restbed/uri.cpp \
    src/corvusoft/restbed/web_socket.cpp \
    src/corvusoft/restbed/web_socket_message.cpp \
    src/corvusoft/restbed/detail/service_impl.cpp \
    src/corvusoft/restbed/detail/session_impl.cpp \
    src/corvusoft/restbed/detail/socket_impl.cpp \
    src/corvusoft/restbed/detail/web_socket_impl.cpp \
    src/corvusoft/restbed/detail/web_socket_manager_impl.cpp

if BUILD_IPC
librestbed_la_SOURCES += src/corvusoft/restbed/detail/ipc_socket_impl.cpp
endif

librestbed_la_CPPFLAGS = \
    -I$(srcdir)/src \
    $(ASIO_CFLAGS)

librestbed_la_CXXFLAGS = \
    $(STD_CXXFLAGS) \
    $(PTHREAD_CFLAGS) \
    -fvisibility=hidden -fvisibility-inlines-hidden \
    -Wall -Wextra -Weffc++ -pedantic \
    -Wno-unknown-pragmas -Wno-deprecated-declarations

# libtool -version-info is current:revision:age (ABI tracking, NOT the package
# version). c-a is the soname major; 5:0:0 yields librestbed.so.5, preserving
# the soname produced by the previous CMake build (SOVERSION 5). On the next
# release bump these per the libtool ABI rules, not the package version.
librestbed_la_LDFLAGS = \
    -version-info 5:0:0 \
    -no-undefined

librestbed_la_LIBADD = $(PTHREAD_LIBS)

if BUILD_SSL
librestbed_la_CPPFLAGS += $(OPENSSL_CFLAGS) -DBUILD_SSL=1
librestbed_la_LIBADD   += $(OPENSSL_LIBS)
endif

if BUILD_IPC
librestbed_la_CPPFLAGS += -DBUILD_IPC=1
endif

if BUILD_WINDOWS
librestbed_la_CPPFLAGS += -DWIN_DLL_EXPORT=1
endif

# Umbrella header: installs as $(includedir)/restbed
umbrelladir = $(includedir)
umbrella_HEADERS = src/restbed

# Public headers: installs into $(includedir)/corvusoft/restbed/
corvusoftrestbeddir = $(includedir)/corvusoft/restbed
corvusoftrestbed_HEADERS = \
    src/corvusoft/restbed/byte.hpp \
    src/corvusoft/restbed/common.hpp \
    src/corvusoft/restbed/logger.hpp \
    src/corvusoft/restbed/request.hpp \
    src/corvusoft/restbed/resource.hpp \
    src/corvusoft/restbed/response.hpp \
    src/corvusoft/restbed/service.hpp \
    src/corvusoft/restbed/session.hpp \
    src/corvusoft/restbed/settings.hpp \
    src/corvusoft/restbed/ssl_settings.hpp \
    src/corvusoft/restbed/status_code.hpp \
    src/corvusoft/restbed/string.hpp \
    src/corvusoft/restbed/uri.hpp \
    src/corvusoft/restbed/web_socket.hpp \
    src/corvusoft/restbed/web_socket_message.hpp

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = restbed.pc

noinst_HEADERS = \
    src/corvusoft/restbed/detail/ipc_socket_impl.hpp \
    src/corvusoft/restbed/detail/request_impl.hpp \
    src/corvusoft/restbed/detail/resource_impl.hpp \
    src/corvusoft/restbed/detail/response_impl.hpp \
    src/corvusoft/restbed/detail/service_impl.hpp \
    src/corvusoft/restbed/detail/session_impl.hpp \
    src/corvusoft/restbed/detail/settings_impl.hpp \
    src/corvusoft/restbed/detail/socket_impl.hpp \
    src/corvusoft/restbed/detail/ssl_settings_impl.hpp \
    src/corvusoft/restbed/detail/uri_impl.hpp \
    src/corvusoft/restbed/detail/web_socket_impl.hpp \
    src/corvusoft/restbed/detail/web_socket_manager_impl.hpp \
    src/corvusoft/restbed/detail/web_socket_message_impl.hpp

# README.md is distributed automatically by automake; LICENSE and the
# remaining project assets must be listed explicitly so they ship in the
# `make dist` tarball. (automake's `foreign` mode auto-distributes COPYING,
# not LICENSE.)
EXTRA_DIST = \
    LICENSE \
    autogen.sh \
    changelog.txt \
    copyright.txt \
    docs \
    legal

DIST_SUBDIRS = test
if BUILD_TESTS
SUBDIRS = test
endif
