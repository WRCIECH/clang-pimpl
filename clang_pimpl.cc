#include "clang_order_fields_master.hh"
#include "command_line_files_keeper.hh"
#include "files_keeper_for_regression_tests.hh"

int main(int argc, const char **argv) {
  ClangOrderFieldsMaster m;
  // auto parsing_result = m.parseArguments(CommandLineFilesKeeper::create(argc,
  // argv));
  FieldsOrderPack pack;
  pack.source_path_list = {"./main.cc"};
  pack.record_name = "Test";
  pack.fields_order = {"b", "a"};
  pack.all_files = {
      "/home/wojciech/Projekty/clang-pimpl/build/tiny_test/main.cc"};
  pack.compile_commands = {clang::tooling::CompileCommand(
      "/home/wojciech/Projekty/clang-pimpl/build/tiny_test",
      "/home/wojciech/Projekty/clang-pimpl/build/tiny_test/main.cc",
      {"/usr/bin/c++", "-o", "CMakeFiles/test_app.dir/main.cc.o", "-c",
       "/home/wojciech/Projekty/clang-pimpl/build/tiny_test/main.cc"},
      "")};
  auto parsing_result =
      m.parseArguments(FilesKeeperForRegressionTests::create(pack));
  if (parsing_result) {
    return -1;
  }
  return m.performRefactoring();
}
