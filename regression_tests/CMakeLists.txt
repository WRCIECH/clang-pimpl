add_executable("RunRegressionTests" 
run_regression_tests.cc
regression_tests_parser.cc
files_keeper_for_regression_tests.cc
)
target_link_libraries("RunRegressionTests" refactor-adapter-lib reorder-fields-lib
definitions-mover-lib
)
# Macro variable to provide location of .include-directories-for-regression-tests file.
add_definitions(-DINCLUDE_DIRECTORIES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB test_directories "clang-*")
foreach(testfile_location ${test_directories})
  file(GLOB files "${testfile_location}/*.txt")
  foreach(file ${files})
    get_filename_component(TestName "${file}" NAME_WE)
    get_filename_component(TestFileName "${file}" NAME)
    add_test (NAME ${TestName} COMMAND "$<TARGET_FILE:RunRegressionTests>" ${TestName} ${file})
  endforeach()
endforeach()
