#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class ExpectFileCommand : public MetacommandExecutor {
public:
  ExpectFileCommand(std::string const &file_name) : file_name_(file_name) {}
  void execute(std::string const &content) override {
    std::cout << "ExpectFileCommand: " << std::quoted(content) << " in file "
              << file_name_ << std::endl;
  }

private:
  std::string file_name_;
};