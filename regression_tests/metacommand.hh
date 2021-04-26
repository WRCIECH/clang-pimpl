#pragma once

#include "../fields_order_pack.hh"
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
  MetacommandExecutor(FieldsOrderPack &state) : state_(state) {}
  virtual ~MetacommandExecutor() = default;
  virtual void execute(std::string const &content) = 0;
  virtual void clear() {}

protected:
  FieldsOrderPack &state_;
};