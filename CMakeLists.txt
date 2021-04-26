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
add_definitions(${LLVM_DEFINITIONS})

# Now build our tools
add_executable(clang-pimpl 
    clang_pimpl.cc
    clang_order_fields_master.cc
    command_line_files_keeper.cc
    files_keeper_for_regression_tests.cc
    PimplAction.cc
)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs option core support irreader)

# Link against LLVM libraries
#target_link_libraries(clang-pimpl ${llvm_libs})
target_link_libraries(clang-pimpl 
${llvm_libs}
clangAST
clangASTMatchers
clangBasic
clangIndex
clangLex
clangSerialization
clangToolingCore
clangBasic
clangFrontend
clangRewrite
clangSerialization
clangTooling
)

add_subdirectory(regression_tests)