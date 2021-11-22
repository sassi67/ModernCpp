cmake_minimum_required(VERSION 3.16)

project(ModernCppTest)

file(GLOB TEST_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h"
)

enable_testing()

add_executable(${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} GTest::gtest benchmark::benchmark ModernCppUtils)
target_include_directories(${PROJECT_NAME} PRIVATE "../src" )