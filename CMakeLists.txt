cmake_minimum_required(VERSION 3.10)
project(X-Log LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "X-Log: Logger for C++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

set(${PROJECT_NAME}_BLD_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(${PROJECT_NAME}_TARGETS_NAME "${PROJECT_NAME}-targets")
set(${PROJECT_NAME}_TARGETS_FILE ${${PROJECT_NAME}_BLD_DIR}/${${PROJECT_NAME}_TARGETS_NAME}.cmake)

set(${PROJECT_NAME}_INC_DIR $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>)
set(${PROJECT_NAME}_SRC_DIR $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(INSTALL_DIR $<INSTALL_INTERFACE:cmake>)
else()
    set(INSTALL_DIR $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}/cmake>)
endif()
set(INS_LIB_DIR ${INSTALL_DIR}/lib)
set(INS_INC_DIR ${INSTALL_DIR}/include)
set(INS_BIN_DIR ${INSTALL_DIR}/bin)

set(${PROJECT_NAME}_PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.hpp
)
set(${PROJECT_NAME}_PRIVATE_INCLUDES
    ${${PROJECT_NAME}_INC_DIR}/errors.hpp
    ${${PROJECT_NAME}_INC_DIR}/format.hpp
    ${${PROJECT_NAME}_INC_DIR}/handler.hpp
    ${${PROJECT_NAME}_INC_DIR}/logger.hpp
    ${${PROJECT_NAME}_INC_DIR}/stl_includes.hpp
)
set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SRC_DIR}/format.cpp
    ${${PROJECT_NAME}_SRC_DIR}/handler.cpp
    ${${PROJECT_NAME}_SRC_DIR}/logger.cpp
)


if(BUILD_TESTING)
    message(STATUS "${PROJECT_NAME}: Building Tests")

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/X-Test)

    find_package(X-Test CONFIG REQUIRED)

    message(STATUS "${PROJECT_NAME}: Tests Built")

    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)


else()
    message(STATUS "${PROJECT_NAME}: Building Library")

    add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_INCLUDES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_INC_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        PUBLIC_HEADER ${${PROJECT_NAME}_PUBLIC_INCLUDES}
        PRIVATE_HEADER ${${PROJECT_NAME}_PRIVATE_INCLUDES} ${${PROJECT_NAME}_SOURCES}
    )

    # creates export to hold compilation requirements
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${${PROJECT_NAME}_TARGETS_NAME}
        RUNTIME DESTINATION ${INS_BIN_DIR}
        LIBRARY DESTINATION ${INS_LIB_DIR}
        ARCHIVE DESTINATION ${INS_LIB_DIR}
        PUBLIC_HEADER DESTINATION ${INS_INC_DIR}
        PRIVATE_HEADER DESTINATION ${INS_INC_DIR}
    )

    # install the export into INSTALL_DIR
    install(EXPORT ${${PROJECT_NAME}_TARGETS_NAME}
        FILE ${${PROJECT_NAME}_TARGETS_FILE}
        DESTINATION ${INSTALL_DIR}
        NAMESPACE xtst::
    )

    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
        "${${PROJECT_NAME}_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${INS_LIB_DIR}
        PATH_VARS ${PROJECT_NAME}_INC_DIR ${PROJECT_NAME}_SRC_DIR ${PROJECT_NAME}_TARGETS_FILE
    )
    write_basic_package_version_file(
        "${${PROJECT_NAME}_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY AnyNewerVersion
    )

    install(FILES
        "${${PROJECT_NAME}_DIR}/${PROJECT_NAME}Config.cmake"
        "${${PROJECT_NAME}_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${INSTALL_DIR}
    )

    # export package to the cmake binary directory
    export(EXPORT ${${PROJECT_NAME}_TARGETS_NAME}
        FILE "${${PROJECT_NAME}_DIR}/${${PROJECT_NAME}_TARGETS_NAME}.cmake"
        NAMESPACE xtst::
    )

    message(STATUS "${PROJECT_NAME}: Finished building")
endif()
