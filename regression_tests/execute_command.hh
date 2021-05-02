#pragma once

#include "files_keeper_for_regression_tests.hh"
#include "metacommand.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(CompilationPack &state) : MetacommandExecutor(state) {}

  int execute(std::string const &content) override {
    std::map<std::string, std::vector<std::string>> commands;

    std::stringstream lines{content};
    for (std::string line{}; std::getline(lines, line, '\n');) {
      std::stringstream words{line};
      std::string command_name;
      words >> command_name;
      for (std::string word{}; std::getline(words, word, ' ');) {
        if (!word.empty()) {
          commands[command_name].emplace_back(word);
        }
      }
    }

    auto m = determineRefactorAdapter();
    auto parsing_result =
        m->parseArguments(FilesKeeperForRegressionTests::create(state_));
    if (parsing_result) {
      std::cout << "Parsing failed!\n";
    }
    return m->performRefactoring(commands);
  }

private:
  std::unique_ptr<RefactorAdapter> determineRefactorAdapter() {
    return std::make_unique<ReorderFieldsRefactorAdapter>();
  }
};