add_executable("RunRegressionTests" 
run_regression_tests.cc
regression_tests_parser.cc
files_keeper_for_regression_tests.cc
)
target_include_directories("RunRegressionTests" PUBLIC "/home/wojciech/libraries/boost_1_74_0")
target_compile_definitions("RunRegressionTests" PUBLIC TESTFILES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries("RunRegressionTests" order-fields-lib)

add_test (NAME TestTwoFieldsStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_two_fields_struct.txt)
add_test (NAME TestThreeFieldsStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_three_fields_struct.txt)
add_test (NAME TestHeaderWithCCFieldsStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_cc_with_header.txt)
add_test (NAME TestWithStdString COMMAND $<TARGET_FILE:RunRegressionTests> test_with_std_string.txt)
add_test (NAME TestTwoSourcesUsingTheSameStruct COMMAND $<TARGET_FILE:RunRegressionTests> test_two_sources_using_the_same_struct.txt)
