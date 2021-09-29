cmake_minimum_required(VERSION 3.10)
project(X-Log LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "X-Log: Logger for C++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/errors.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/format.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/handler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/logger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/stl_includes.hpp
    DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR}
)


if(NOT RUN_X_LOG_TESTS)
    message(STATUS "X-Log: RUN_X_LOG_TESTS unspecified; defaulting to 1")
    set(RUN_X_LOG_TESTS True)
endif()


if(${RUN_X_LOG_TESTS})
    message(STATUS "X-Log: Building Tests")
    find_package(X_Test CONFIG REQUIRED)
    add_executable(X-LogTests ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)
    message(STATUS "X-Log: Tests Built to 'X-LogTests'")

else()
    message(STATUS "X-Log: Building Library")
    add_library(X-Log SHARED X-Log.hpp)
    set_target_properties(X-Log PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(X-Log PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

    install(TARGETS X-Log
        EXPORT X-LogTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )

    install(EXPORT X-LogTargets
        FILE X-LogTargets.cmake
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
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/X-Log
    )
endif()
