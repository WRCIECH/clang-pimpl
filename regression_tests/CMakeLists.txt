
add_executable("RunRegressionTests" 
"${CMAKE_CURRENT_SOURCE_DIR}/run_regression_tests.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/regression_tests_parser.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/metacommand.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/execute_command.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/given_filesystem_command.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/given_file_command.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/expect_file_command.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/storage.hh"
"${CMAKE_CURRENT_SOURCE_DIR}/storage.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/../clang_order_fields_master.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/../command_line_files_keeper.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/../files_keeper_for_regression_tests.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/../PimplAction.cc"
)
target_include_directories("RunRegressionTests" PUBLIC "/home/wojciech/libraries/boost_1_74_0")
# target_link_libraries("RunRegressionTests" "${CMAKE_PROJECT_NAME}")

target_compile_definitions("RunRegressionTests" PUBLIC TESTFILES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries("RunRegressionTests"
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

add_test (NAME TestTwoFieldsStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_two_fields_struct.txt)
