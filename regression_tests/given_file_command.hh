#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class GivenFileCommand : public MetacommandExecutor {
public:
  GivenFileCommand(GlobalState &state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  void execute(std::string const &content) override {
    int fd{0};
    auto op_result =
        llvm::sys::fs::openFileForWrite(state_.files_map[file_name_], fd);
    llvm::raw_fd_ostream file_writer(fd, true);
    file_writer << content;
  }

private:
  std::string file_name_;
};
