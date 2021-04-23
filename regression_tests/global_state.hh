#pragma once

#include "llvm/Support/FileSystem.h"
#include <map>
#include <string>

class GlobalState {
public:
  std::map<std::string, llvm::SmallString<128>> files_map;
};