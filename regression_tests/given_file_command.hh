#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class GivenFileCommand : public MetacommandExecutor {
public:
  GivenFileCommand(std::string const &file_name) : file_name_(file_name) {}
  void execute(std::string const &content) override {
    std::cout << "GivenFileCommand: " << std::quoted(content) << " in file "
              << file_name_ << std::endl;
  }

private:
  std::string file_name_;
};
