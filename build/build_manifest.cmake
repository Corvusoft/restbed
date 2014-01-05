# Copyright (c) 2013, 2014 Corvusoft

#
# Build manifest
#
set( MANIFEST
	${FRAMEWORK_SOURCE_DIR}/settings.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/settings_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/status_code.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/status_code_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/method.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/method_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/resource.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/resource_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/request.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/request_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/request_builder_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/response.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/response_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/service.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/service_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/regex.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/map.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/date.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/string.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/istream.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/resource_matcher_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/path_parameter_impl.cpp
)
