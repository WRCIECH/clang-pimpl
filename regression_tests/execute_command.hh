#pragma once

#include "files_keeper_for_regression_tests.hh"
#include "metacommand.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_options_adapter.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(CompilationPack *state) : MetacommandExecutor(state) {}

  int execute(std::string const &content) override {

    auto m = determineRefactorAdapter();

    auto parsing_result =
        m->parseArguments(FilesKeeperForRegressionTests::create(
            state_,
            std::make_shared<ReorderFieldsOptionsAdapterForRegressionTests>(
                content)));
    if (parsing_result) {
      std::cerr << "Parsing failed!\n";
    }
    return m->performRefactoring();
  }

private:
  std::unique_ptr<RefactorAdapter> determineRefactorAdapter() {
    return std::make_unique<ReorderFieldsRefactorAdapter>();
  }
};