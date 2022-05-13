cmake_minimum_required( VERSION 3.21 )
project( Awake )

set( CMAKE_CXX_STANDARD 20 )

add_library( Awake_lib
             IO/CmdLnArgParser.cpp IO/CmdLnArgParser.hpp
             IO/Messenger.cpp IO/Messenger.hpp
             Misc/Conversions.cpp Misc/Conversions.hpp )

add_compile_options( -v )
add_executable( awake main.cpp )
target_link_libraries( awake Awake_lib )

install( TARGETS awake )