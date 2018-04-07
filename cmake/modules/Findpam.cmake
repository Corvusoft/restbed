find_library( pam_LIBRARY pam HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_path( pam_INCLUDE security/pam_appl.h HINTS "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( pam_INCLUDE AND pam_LIBRARY )
    set( PAM_FOUND TRUE )

    message( STATUS "Found PAM include at: ${pam_INCLUDE}" )
    message( STATUS "Found PAM library at: ${pam_LIBRARY}" )
else ( )
    message( STATUS "Failed to locate PAM, skipping example." )
endif ( )
