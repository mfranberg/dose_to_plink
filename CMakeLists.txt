project( dose_to_plink )

cmake_minimum_required( VERSION 2.7 )

set( DOSE_TO_PLINK_VERSION_MAJOR 0 )
set( DOSE_TO_PLINK_VERSION_MINOR 1 )
set( DOSE_TO_PLINK_VERSION_PATCH 0 )

include_directories( "libs/" )
add_definitions( -DGZSTREAM_NAMESPACE=gz )

add_subdirectory( libs )
add_subdirectory( src )


set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "dose_to_plink-1.0.0")
set(CPACK_SOURCE_STRIP_FILES "")
set(CPACK_SOURCE_IGNORE_FILES "/build;.*~;.git*")
SET(CPACK_PACKAGE_NAME "dose_to_plink")
SET(CPACK_PACKAGE_VENDOR "Mattias Franberg")
SET(CPACK_PACKAGE_VERSION "1.0.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")


include(CPack)
