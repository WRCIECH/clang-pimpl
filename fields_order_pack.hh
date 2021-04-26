#pragma once

#include "clang/Tooling/CompilationDatabase.h"
#include <map>
#include <vector>

struct FieldsOrderPack {
  std::vector<std::string> source_path_list;
  std::string record_name;
  std::vector<std::string> fields_order;
  std::vector<std::string> all_files;
  std::vector<clang::tooling::CompileCommand> compile_commands;

  // Used to find file paths in regression tests. Not transmitted to refactor
  // tools.
  std::map<std::string, std::string> file_name_to_path;
};
