AM_CPPFLAGS = \
    -I$(top_srcdir)/src \
    $(ASIO_CFLAGS) \
    $(CATCH2_CFLAGS)

if BUILD_SSL
AM_CPPFLAGS += $(OPENSSL_CFLAGS) -DBUILD_SSL=1
endif

if BUILD_IPC
AM_CPPFLAGS += -DBUILD_IPC=1
endif

AM_CXXFLAGS = $(STD_CXXFLAGS) $(PTHREAD_CFLAGS)

LDADD = $(top_builddir)/librestbed.la $(CATCH2_LIBS) $(PTHREAD_LIBS)

if BUILD_TESTS
check_PROGRAMS = \
    uri_unit_suite \
    string_unit_suite \
    session_unit_suite \
    service_unit_suite \
    request_unit_suite \
    settings_unit_suite \
    response_unit_suite \
    resource_unit_suite \
    ssl_settings_unit_suite \
    web_socket_message_unit_suite \
    request_integration_suite \
    string_integration_suite \
    session_integration_suite \
    resource_integration_suite \
    response_integration_suite \
    ssl_settings_integration_suite \
    settings_integration_suite \
    service_integration_suite \
    web_socket_message_integration_suite \
    missing_regex_support_regression_suite \
    resource_error_handler_overflow_regression_suite \
    service_error_handler_overflow_regression_suite \
    ssl_settings_to_handle_windows_paths_regression_suite \
    uncaught_exception_when_peer_closes_connection_regression_suite \
    uri_fails_to_handle_file_scheme_relative_paths_regression_suite \
    uri_get_parameter_fails_to_handle_empty_values_regression_suite \
    uri_encode_fails_to_handle_high_bytes_regression_suite \
    uri_get_port_overflow_regression_suite \
    string_replace_infinite_loop_regression_suite \
    web_socket_frame_parse_regression_suite \
    web_socket_extended_length_read_regression_suite \
    web_socket_malformed_frame_regression_suite \
    web_socket_extended_length_boundary_regression_suite \
    web_socket_error_handler_once_regression_suite \
    web_socket_masked_compose_roundtrip_regression_suite \
    service_sanitised_route_bookkeeping_regression_suite \
    string_join_trailing_delimiter_regression_suite \
    parse_parameter_strictness_regression_suite \
    service_http_version_locale_regression_suite

if BUILD_IPC
check_PROGRAMS += ipc_connection_timeout_error_handler_regression_suite
endif

TESTS = $(check_PROGRAMS)

# Port-binding suites bind on port 0 (OS-assigned ephemeral) and discover the
# bound port via the ready handler, so they no longer collide and `make check`
# is safe to run in parallel.

# Unit tests
uri_unit_suite_SOURCES                    = uri_unit_suite.cpp
string_unit_suite_SOURCES                 = string_unit_suite.cpp
session_unit_suite_SOURCES                = session_unit_suite.cpp
service_unit_suite_SOURCES                = service_unit_suite.cpp
request_unit_suite_SOURCES                = request_unit_suite.cpp
settings_unit_suite_SOURCES               = settings_unit_suite.cpp
response_unit_suite_SOURCES               = response_unit_suite.cpp
resource_unit_suite_SOURCES               = resource_unit_suite.cpp
ssl_settings_unit_suite_SOURCES           = ssl_settings_unit_suite.cpp
web_socket_message_unit_suite_SOURCES     = web_socket_message_unit_suite.cpp

# Integration tests
request_integration_suite_SOURCES         = request_integration_suite.cpp
string_integration_suite_SOURCES          = string_integration_suite.cpp
session_integration_suite_SOURCES         = session_integration_suite.cpp
resource_integration_suite_SOURCES        = resource_integration_suite.cpp
response_integration_suite_SOURCES        = response_integration_suite.cpp
ssl_settings_integration_suite_SOURCES    = ssl_settings_integration_suite.cpp
settings_integration_suite_SOURCES        = settings_integration_suite.cpp
service_integration_suite_SOURCES         = service_integration_suite.cpp
web_socket_message_integration_suite_SOURCES = web_socket_message_integration_suite.cpp

# Regression tests
missing_regex_support_regression_suite_SOURCES                         = missing_regex_support_regression_suite.cpp
resource_error_handler_overflow_regression_suite_SOURCES               = resource_error_handler_overflow_regression_suite.cpp
service_error_handler_overflow_regression_suite_SOURCES                = service_error_handler_overflow_regression_suite.cpp
ssl_settings_to_handle_windows_paths_regression_suite_SOURCES           = ssl_settings_to_handle_windows_paths_regression_suite.cpp
uncaught_exception_when_peer_closes_connection_regression_suite_SOURCES = uncaught_exception_when_peer_closes_connection_regression_suite.cpp
uri_fails_to_handle_file_scheme_relative_paths_regression_suite_SOURCES = uri_fails_to_handle_file_scheme_relative_paths_regression_suite.cpp
uri_get_parameter_fails_to_handle_empty_values_regression_suite_SOURCES = uri_get_parameter_fails_to_handle_empty_values_regression_suite.cpp
uri_encode_fails_to_handle_high_bytes_regression_suite_SOURCES         = uri_encode_fails_to_handle_high_bytes_regression_suite.cpp
uri_get_port_overflow_regression_suite_SOURCES                         = uri_get_port_overflow_regression_suite.cpp
string_replace_infinite_loop_regression_suite_SOURCES                  = string_replace_infinite_loop_regression_suite.cpp

# This suite exercises restbed::detail::WebSocketManagerImpl, whose symbols are
# compiled with hidden visibility and therefore absent from the shared library's
# dynamic symbol table. Force a static link so the detail symbols resolve.
web_socket_frame_parse_regression_suite_SOURCES                        = web_socket_frame_parse_regression_suite.cpp
web_socket_frame_parse_regression_suite_LDFLAGS                        = -static

# Exercises restbed::detail::WebSocketImpl, whose symbols are hidden in the
# shared library; static link so the detail symbols resolve.
web_socket_extended_length_read_regression_suite_SOURCES               = web_socket_extended_length_read_regression_suite.cpp
web_socket_extended_length_read_regression_suite_LDFLAGS               = -static

# Exercises restbed::detail::WebSocketImpl, whose symbols are hidden in the
# shared library; static link so the detail symbols resolve.
web_socket_malformed_frame_regression_suite_SOURCES                    = web_socket_malformed_frame_regression_suite.cpp
web_socket_malformed_frame_regression_suite_LDFLAGS                    = -static

web_socket_extended_length_boundary_regression_suite_SOURCES           = web_socket_extended_length_boundary_regression_suite.cpp

web_socket_error_handler_once_regression_suite_SOURCES                 = web_socket_error_handler_once_regression_suite.cpp

# Exercises restbed::detail::WebSocketManagerImpl, whose symbols are hidden in
# the shared library; static link so the detail symbols resolve.
web_socket_masked_compose_roundtrip_regression_suite_SOURCES           = web_socket_masked_compose_roundtrip_regression_suite.cpp
web_socket_masked_compose_roundtrip_regression_suite_LDFLAGS           = -static

service_sanitised_route_bookkeeping_regression_suite_SOURCES           = service_sanitised_route_bookkeeping_regression_suite.cpp

string_join_trailing_delimiter_regression_suite_SOURCES                = string_join_trailing_delimiter_regression_suite.cpp

parse_parameter_strictness_regression_suite_SOURCES                    = parse_parameter_strictness_regression_suite.cpp

# Exercises restbed::detail::ServiceImpl, whose symbols are hidden in the
# shared library; static link so the detail symbols resolve.
service_http_version_locale_regression_suite_SOURCES                   = service_http_version_locale_regression_suite.cpp
service_http_version_locale_regression_suite_LDFLAGS                   = -static

if BUILD_IPC
ipc_connection_timeout_error_handler_regression_suite_SOURCES          = ipc_connection_timeout_error_handler_regression_suite.cpp
endif
endif
