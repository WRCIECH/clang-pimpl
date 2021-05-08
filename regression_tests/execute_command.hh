#pragma once

#include "files_keeper_for_regression_tests.hh"
#include "metacommand.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_options_adapter.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(CompilationPack *state, std::string const &refactor_name)
      : MetacommandExecutor(state), refactor_name_(refactor_name) {}

  int execute(std::string const &content) override {

    auto m = determineRefactorAdapter();
    if (!m) {
      std::cerr << refactor_name_ << " refactoring not recognized!\n";
      return -1;
    }

    auto parsing_result =
        m->parseArguments(FilesKeeperForRegressionTests::create(
            state_,
            std::make_shared<ReorderFieldsOptionsAdapterForRegressionTests>(
                content)));
    if (parsing_result) {
      std::cerr << "ExecuteCommand: parsing failed for refactor "
                << refactor_name_ << "!\n";
      return -1;
    }
    return m->performRefactoring();
  }

private:
  std::unique_ptr<RefactorAdapter> determineRefactorAdapter() {
    if (refactor_name_ == "clang-reorder-fields") {
      return std::make_unique<ReorderFieldsRefactorAdapter>();
    }
    return nullptr;
  }
  std::string refactor_name_;
};