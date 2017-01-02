# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.

find_library( pam_LIBRARY pam HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_path( pam_INCLUDE security/pam_appl.h HINTS "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( pam_INCLUDE AND pam_LIBRARY )
    set( PAM_FOUND TRUE )

    message( STATUS "${Green}Found PAM include at: ${pam_INCLUDE}${Reset}" )
    message( STATUS "${Green}Found PAM library at: ${pam_LIBRARY}${Reset}" )
else ( )
    message( STATUS "${Yellow}Failed to locate PAM, skipping example.${Reset}" )
endif ( )
