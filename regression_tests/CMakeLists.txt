add_executable("RunRegressionTests" 
run_regression_tests.cc
regression_tests_parser.cc
files_keeper_for_regression_tests.cc
)
target_include_directories("RunRegressionTests" PUBLIC "/home/wojciech/libraries/boost_1_74_0")
target_compile_definitions("RunRegressionTests" PUBLIC TESTFILES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries("RunRegressionTests" order-fields-lib)

add_test (NAME TestTwoFieldsStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_two_fields_struct.txt)
