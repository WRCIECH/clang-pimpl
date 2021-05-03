#pragma once

#include "clang/Tooling/CompilationDatabase.h"
#include <iostream>
#include <vector>

struct CompilationPack {
  std::vector<std::string> source_path_list;
  std::vector<std::string> all_files;
  std::vector<clang::tooling::CompileCommand> compile_commands;
  std::string findPath(std::string const &file_name) const {
    for (int i = 0; i < all_files.size(); ++i) {
      if (all_files[i] == file_name) {
        return source_path_list[i];
      }
    }
    return "";
  }
};
