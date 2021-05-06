#pragma once

#include "clang/Tooling/CompilationDatabase.h"
#include <iostream>
#include <map>
#include <set>
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

  bool filenameNotChecked(std::string const &filename) {
    return checked_files.count(filename) < 1;
  }
  // Variables needed for post-checking.
  std::set<std::string> checked_files;
  std::map<std::string, std::string> initial_files_map;
  bool filestructure_checked{false};
  std::map<std::string, std::string> file_content_map;
};
