#include "refactor_adapter/command_line_files_keeper.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_options_adapter.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"

int main(int argc, const char **argv) {
  std::unique_ptr<RefactorAdapter> m =
      std::make_unique<ReorderFieldsRefactorAdapter>();
  auto parsing_result = m->parseArguments(CommandLineFilesKeeper::create(
      argc, argv,
      std::make_shared<ReorderFieldsOptionsAdapterForCommandLine>()));
  if (parsing_result) {
    return -1;
  }
  return m->performRefactoring();
}
