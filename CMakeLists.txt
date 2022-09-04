cmake_minimum_required( VERSION 3.21 )
project( Awake )

if( NOT DEFINED ENV{BASE_DIR} )
    message( FATAL_ERROR "`ENV\${BASE_DIR}` is not set. Make sure to source `setup_base.sh`, which is in `Base/`." )
else()
    message( STATUS "`$ENV{BASE_DIR}` is set to `{BASE_DIR}`." )
endif()

set( CMAKE_CXX_STANDARD 20 )

add_subdirectory( $ENV{BASE_DIR} $ENV{BASE_DIR}/build )

add_executable( ${PROJECT_NAME} Awake.cpp )

target_link_libraries( Awake Base )

add_compile_options( -v )

install( TARGETS Awake )
