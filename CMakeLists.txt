cmake_minimum_required(VERSION 3.17.0)

project(clang-pimpl)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
include (CTest)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${LLVM_CMAKE_DIR}"
  "${CLANG_CMAKE_DIR}"
  )


message(STATUS "cmake module path: ${CMAKE_MODULE_PATH}")
# import LLVM CMake functions
include(AddLLVM)
include(AddClang)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++2a")

message(STATUS "clang source dir: ${CLANG_SOURCE_DIR}")
message(STATUS "clang include dirs: ${CLANG_INCLUDE_DIRS}")
message(STATUS "clang definitions: ${CLANG_DEFINITIONS}")

message(STATUS "cmake cxx flags ${CMAKE_CXX_FLAGS}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Found Clang ${CLANG_VERSION_MAJOR}")
 
message(STATUS "Clang install prefix: ${CLANG_INSTALL_PREFIX}")
message(STATUS "Clang cmake dir: ${CLANG_CMAKE_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
include_directories("/home/wojciech/libraries/boost_1_74_0")

add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(refactor_adapter)
add_subdirectory(refactor_tools)
add_subdirectory(regression_tests)
add_subdirectory(executables)