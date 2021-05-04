#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class GivenFileCommand : public MetacommandExecutor {
public:
  GivenFileCommand(CompilationPack *state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  int execute(std::string const &content) override {
    auto file_path = state_->findPath(file_name_);
    if (file_path.empty()) {
      std::cerr << "GivenFileCommand: " << file_name_
                << "file was not found !!! \n";
      return -1;
    }

    int fd{0};
    auto op_result = llvm::sys::fs::openFileForWrite(file_path, fd);
    llvm::raw_fd_ostream file_writer(fd, true);
    file_writer << content;

    return 0;
  }

private:
  std::string file_name_;
};
