#pragma once

#include "compilation_pack.hh"
#include "llvm/Support/FileSystem.h"
#include <iomanip>
#include <iostream>
#include <string>

enum class Metacommand {
  GIVEN_FILESYSTEM,
  GIVEN_FILE,
  EXECUTE,
  EXPECT_FILE,
  END
};

class MetacommandExecutor {
public:
  MetacommandExecutor(CompilationPack &state) : state_(state) {}
  virtual ~MetacommandExecutor() = default;
  virtual int execute(std::string const &content) = 0;

protected:
  CompilationPack &state_;
};