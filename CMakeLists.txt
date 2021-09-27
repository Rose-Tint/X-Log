cmake_minimum_required ( VERSION 3.10 )

project ( XLog LANGUAGES CXX VERSION 1.0 DESCRIPTION "X-Log" )

add_definitions(-std=c++17)

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED True )

if ( USE_X_LOG )
    add_subdirectory ( X-Log )
    list ( APPEND EXTRA_LIBS XLogSrc )
    list ( APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/X-Log" )
endif ( )

target_link_libraries ( XLog PUBLIC ${EXTRA_LIBS} )

target_include_directories ( XLog PUBLIC ${EXTRA_INCLUDES} )

set_target_properties( XLog PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/X-Log.hpp
)

install (
    TARGETS mylib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
