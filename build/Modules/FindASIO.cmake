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

find_path( ASIO_INCLUDE_DIR asio.hpp "/usr/include" "/usr/local/include" )

if ( ASIO_INCLUDE_DIR )
    set( ASIO_FOUND TRUE )
endif ( ASIO_INCLUDE_DIR )

if ( ASIO_FOUND )
    if ( NOT ASIO_FIND_QUIETLY )
	message( STATUS "Found asio.hpp header file: ${ASIO_INCLUDE_DIR}" )
    endif ( NOT ASIO_FIND_QUIETLY )
else ( ASIO_FOUND )
    if ( ASIO_FIND_REQUIRED )
	if ( NOT ASIO_INCLUDE_DIR )
	    message( FATAL_ERROR "Could not find asio.hpp header file!" )
	endif ( NOT GPG_ERROR_INCLUDE_DIR )
    endif ( ASIO_FIND_REQUIRED )
endif ( ASIO_FOUND )
