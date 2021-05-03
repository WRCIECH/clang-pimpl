#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <fstream>
#include <sstream>

class ExpectFileCommand : public MetacommandExecutor {
public:
  ExpectFileCommand(CompilationPack *state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  int execute(std::string const &expected_file_content) override {
    auto file_path = state_->findPath(file_name_);
    if (file_path.empty()) {
      std::cerr << "ExpectFileCommand: " << file_name_
                << "file was not found !!! \n";
      return -1;
    }

    std::ifstream modified_file{file_path};
    std::stringstream modified_content;
    modified_content << modified_file.rdbuf();

    std::cout << "Modified: " << modified_content.str() << std::endl;
    std::cout << "Expected: " << expected_file_content << std::endl;

    if (modified_content.str() == expected_file_content) {
      return 0;
    }
    return -1;
  }

private:
  std::string file_name_;
};