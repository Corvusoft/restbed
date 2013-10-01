# Site: restbed.corvusoft.co.uk
# Author: Ben Crowhurst
#
# Copyright (c) 2013 Restbed Core Development Team and Community Contributors
#
# This file is part of Restbed.
#
# Restbed is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Restbed is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Lesser GNU General Public License for more details.
#
# You should have received a copy of the Lesser GNU General Public License
# along with Restbed.  If not, see <http://www.gnu.org/licenses/>.

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
	${FRAMEWORK_SOURCE_DIR}/detail/request_builder.cpp
	${FRAMEWORK_SOURCE_DIR}/response.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/response_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/service.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/service_impl.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/map.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/string.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/helpers/istream.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/resource_matcher.cpp
	${FRAMEWORK_SOURCE_DIR}/detail/path_parameter.cpp
)
