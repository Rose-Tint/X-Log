cmake_minimum_required(VERSION 3.10)
project(X-Log VERSION 1.0.0)
set(INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/Export/)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(X-Log INTERFACE)
add_library(X-Log::X-Log ALIAS X-Log)

target_include_directories(X-Log INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${INC_DIR}>
    $<BUILD_INTERFACE:${SRC_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_sources(X-Log INTERFACE
    /inc/errors.cpp
    /inc/filter.cpp
    /inc/format.cpp
    /inc/fwd_declares.cpp
    /inc/handler.cpp
    /inc/logger.cpp
    /inc/logstream.cpp
    /inc/record.cpp
)


find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(X-Log INTERFACE
    Boost::boost
    Threads::Threads
)


include(CMakePackageConfigHelpers)
install(TARGETS X-Log EXPORT X-LogTargets)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/inc/ DESTINATION include)

install(EXPORT X-LogTargets
    FILE X-LogTargets.cmake
    NAMESPACE X-Log::
    DESTINATION lib/cmake/X-Log
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/X-LogConfig.cmake"
    INSTALL_DESTINATION lib/cmake/X-Log
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/X-LogConfig.cmake"
    DESTINATION lib/cmake/X-Log
)


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${X-Log_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${X-Log_VERSION_MINOR})
set(CPACK_PACKAGE_NAME "X-Log")
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
include(CPack)
