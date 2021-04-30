cmake_minimum_required(VERSION 3.17.0)

project(clang-pimpl)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED)
include (CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++2a")

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Found Clang ${CLANG_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(clang_order_fields)
add_subdirectory(executables)
add_subdirectory(regression_tests)