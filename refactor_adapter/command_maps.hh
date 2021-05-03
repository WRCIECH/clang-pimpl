#pragma once

#include "clang/Tooling/Refactoring.h"
#include <map>

struct CommandMaps {
  std::map<std::string, llvm::StringRef> string_map;
  std::map<std::string, llvm::ArrayRef<std::string>> array_map;
};
