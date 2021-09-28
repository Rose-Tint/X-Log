cmake_minimum_required(VERSION 3.10)
project(X_Log LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "X-Log: Logger for C++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(X_Log SHARED X-Log.hpp)

target_include_directories(X_Log
    PRIVATE   "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
)

install(TARGETS X_Log
    EXPORT X_Log
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES
    inc/errors.hpp
    inc/format.hpp
    inc/handler.hpp
    inc/logger.hpp
    inc/stl_includes.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT X_Log
    FILE X-LogLib.cmake
    NAMESPACE xlog::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/X-Log
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/X-Log.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/X-Log
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/X-LogConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/X-LogConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/X-Log
)


if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Testing")
	set(CMAKE_BUILD_TYPE "Testing")
endif()

if (CMAKE_BUILD_TYPE EQUAL "Testing")
    add_executable(tests/main.cpp)
endif()
