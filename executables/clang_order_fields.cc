#include "refactor_adapter/command_line_files_keeper.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"

int main(int argc, const char **argv) {
  std::unique_ptr<RefactorAdapter> m =
      std::make_unique<ReorderFieldsRefactorAdapter>();
  auto file_keeper = CommandLineFilesKeeper::create(argc, argv);
  auto commands = file_keeper->getCommands();
  auto parsing_result = m->parseArguments(std::move(file_keeper));
  if (parsing_result) {
    return -1;
  }
  return m->performRefactoring(commands);
}
