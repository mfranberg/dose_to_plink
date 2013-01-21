include_directories( "." )

file( GLOB SRC_LIST "*.cpp" )
add_executable( dose_to_plink ${SRC_LIST} )

target_link_libraries( dose_to_plink gzstream optparse )
