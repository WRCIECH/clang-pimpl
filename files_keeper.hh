#pragma once

#include "llvm/Support/raw_ostream.h"
#include <string>
#include <vector>

namespace llvm {
class Error;
class StringRef;
template <typename T> class ArrayRef;

} // namespace llvm

namespace clang {
namespace tooling {
class CompilationDatabase;
}
} // namespace clang

class FilesKeeper {
public:
  virtual bool isOk() = 0;
  virtual llvm::Error getError() = 0;
  virtual ~FilesKeeper() = default;

  virtual const std::vector<std::string> *getSourcePathList() = 0;
  virtual clang::tooling::CompilationDatabase *getCompilations() = 0;
  virtual llvm::StringRef getRecordName() const = 0;
  virtual llvm::ArrayRef<std::string> getDesiredFieldsOrder() const = 0;
  virtual bool isInplace() const = 0;
};