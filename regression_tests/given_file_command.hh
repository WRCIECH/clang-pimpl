#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class GivenFileCommand : public MetacommandExecutor {
public:
  GivenFileCommand(CompilationPack &state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  int execute(std::string const &content) override {
    std::cout << "GivenFile command! " << file_name_ << "\n";
    int fd{0};
    auto it = state_.file_name_to_path.find(file_name_);
    if (it == state_.file_name_to_path.end()) {
      std::cout << "GivenFileCommand: " << file_name_
                << " file was not found !!! \n";
      return -1;
    }

    auto op_result = llvm::sys::fs::openFileForWrite(it->second, fd);
    llvm::raw_fd_ostream file_writer(fd, true);
    file_writer << content;

    return 0;
  }

private:
  std::string file_name_;
};
