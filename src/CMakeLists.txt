cmake_minimum_required(VERSION 3.16)

project(ModernCppApp C CXX)

add_subdirectory(utils)

file(GLOB SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ModernCppUtils)