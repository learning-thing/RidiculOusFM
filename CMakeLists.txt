cmake_minimum_required(VERSION 3.29.2)
project( TinoVision )

#include_directories( lib/ )
include_directories( src/lib/ )
include_directories( src/include )

add_executable( main src/main.cpp )
target_link_libraries(main raylib)
