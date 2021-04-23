#pragma once

#include "global_state.hh"
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
  MetacommandExecutor(GlobalState &state) : state_(state) {}
  virtual ~MetacommandExecutor() = default;
  virtual void execute(std::string const &content) = 0;
  virtual void clear() {}

protected:
  GlobalState &state_;
};

class ExpectStdoutCommand : public MetacommandExecutor {
public:
  ExpectStdoutCommand(GlobalState &state) : MetacommandExecutor(state) {}
  void execute(std::string const &content) override {
    std::cout << "ExpectStdoutCommand: " << std::quoted(content) << std::endl;
  }
};