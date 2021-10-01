add_executable(Test main.cpp)
target_sources(Test PUBLIC
    ${CMAKE_SOURCE_DIR}/src/format.cpp
    ${CMAKE_SOURCE_DIR}/src/handler.cpp
    ${CMAKE_SOURCE_DIR}/src/logger.cpp
)

target_include_directories(Test PUBLIC ${CMAKE_SOURCE_DIR}/inc)

add_test(X-Log-test COMMAND "Test")
