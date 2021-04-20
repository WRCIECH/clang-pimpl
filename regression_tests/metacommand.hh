#pragma once

#include "llvm/Support/FileSystem.h"
#include <iomanip>
#include <iostream>
#include <string>

enum class Metacommand {
  GIVEN_FILESYSTEM,
  GIVEN_FILE,
  EXECUTE,
  EXPECT_STDOUT,
  EXPECT_FILE,
  END
};

class MetacommandExecutor {
public:
  virtual ~MetacommandExecutor() = default;
  virtual void execute(std::string const &content) = 0;
};

class ExpectStdoutCommand : public MetacommandExecutor {
public:
  ExpectStdoutCommand() {}
  void execute(std::string const &content) override {
    std::cout << "ExpectStdoutCommand: " << std::quoted(content) << std::endl;
  }
};