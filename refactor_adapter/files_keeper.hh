#pragma once

#include "command_maps.hh"
#include "options_adapter.hh"
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
  FilesKeeper(std::shared_ptr<OptionsAdapter> options_adapter)
      : options_adapter_(std::move(options_adapter)) {}
  virtual bool isOk() = 0;
  virtual llvm::Error getError() = 0;
  virtual ~FilesKeeper() = default;

  virtual const std::vector<std::string> *getSourcePathList() = 0;
  virtual clang::tooling::CompilationDatabase *getCompilations() = 0;
  virtual bool isInplace() const = 0;
  CommandMaps const &getCommands() const {
    return options_adapter_->getCommands();
  }

protected:
  std::shared_ptr<OptionsAdapter> options_adapter_;
};