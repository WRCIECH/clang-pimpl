#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class ExecuteCommand : public MetacommandExecutor {
public:
  ExecuteCommand(GlobalState &state) : MetacommandExecutor(state) {}
  void execute(std::string const &content) override {
    std::cout << "ExecuteCommand: " << std::quoted(content) << std::endl;
  }
};