#pragma once

#include "clang_order_fields/clang_order_fields_master.hh"
#include "files_keeper_for_regression_tests.hh"
#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(FieldsOrderPack &state) : MetacommandExecutor(state) {}
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

    if (commands.count("record-name") > 0) {
      state_.record_name = commands["record-name"][0];
    } else {
      std::cout << "record-name command not recognized\n";
    }
    if (commands.count("fields-order") > 0) {
      state_.fields_order = commands["fields-order"];
    } else {
      std::cout << "fields-order command not recognized\n";
    }

    ClangOrderFieldsMaster m;
    auto parsing_result =
        m.parseArguments(FilesKeeperForRegressionTests::create(state_));
    if (parsing_result) {
      std::cout << "Parsing failed!\n";
    }
    return m.performRefactoring();
  }
};