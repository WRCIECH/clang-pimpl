#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"

class ExpectFileCommand : public MetacommandExecutor {
public:
  ExpectFileCommand(FieldsOrderPack &state, std::string const &file_name)
      : MetacommandExecutor(state), file_name_(file_name) {}
  int execute(std::string const &expected_file_content) override {
    auto file_path = state_.file_name_to_path[file_name_];

    // std::cout << "Does result equal to expected? " << std::boolalpha
    //           << (state_.output == expected_file_content) << std::endl;
    if (state_.output == expected_file_content) {
      return 0;
    }
    return -1;
  }

private:
  std::string file_name_;
};