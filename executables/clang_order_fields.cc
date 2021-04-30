#include "clang_order_fields/clang_order_fields_master.hh"
#include "command_line_files_keeper.hh"

int main(int argc, const char **argv) {
  ClangOrderFieldsMaster m;
  auto parsing_result =
      m.parseArguments(CommandLineFilesKeeper::create(argc, argv));
  if (parsing_result) {
    return -1;
  }
  return m.performRefactoring();
}
