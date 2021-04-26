#pragma once

#include "../clang_order_fields_master.hh"
#include "../files_keeper_for_regression_tests.hh"
#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(FieldsOrderPack &state) : MetacommandExecutor(state) {}
  void execute(std::string const &content) override {
    state_.record_name = "Test";
    state_.fields_order = {"b", "a"};

    ClangOrderFieldsMaster m;
    auto parsing_result =
        m.parseArguments(FilesKeeperForRegressionTests::create(state_));
    if (parsing_result) {
      std::cout << "Parsing failed!\n";
    }
    m.performRefactoring();
  }
};