#pragma once

#include "llvm/Support/FileSystem.h"

class Storage {
public:
  virtual ~Storage() {}
  virtual void clean() = 0;
};

class FilesStorage : public Storage {
public:
  FilesStorage() = default;
  ~FilesStorage() override;
  void clean() override;
};