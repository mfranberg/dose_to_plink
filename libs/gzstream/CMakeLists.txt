include_directories( "." )

add_library( gzstream gzstream.cpp )
target_link_libraries( gzstream -lz )
