#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class GivenFileCommand : public MetacommandExecutor {
public:
  GivenFileCommand(FieldsOrderPack &state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  void execute(std::string const &content) override {
    int fd{0};
    auto it = state_.file_name_to_path.find(file_name_);
    if (it == state_.file_name_to_path.end()) {
      std::cout << "File was not found !!! \n";
      return;
    }

    auto op_result = llvm::sys::fs::openFileForWrite(it->second, fd);
    llvm::raw_fd_ostream file_writer(fd, true);
    file_writer << content;
  }

private:
  std::string file_name_;
};
