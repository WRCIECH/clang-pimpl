#pragma once

#include "command_maps.hh"
#include "files_keeper.hh"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include <memory>
#include <vector>

namespace llvm {
template <typename T> class Expected;
} // namespace llvm

namespace clang {
namespace tooling {
class CommonOptionsParser;
} // namespace tooling
} // namespace clang

class CommandLineFilesKeeper : public FilesKeeper {
public:
  CommandLineFilesKeeper(
      int argc, const char **argv,
      std::shared_ptr<OptionsAdapterForCommandLine> options_adapter);

  static std::unique_ptr<CommandLineFilesKeeper>
  create(int argc, const char **argv,
         std::shared_ptr<OptionsAdapterForCommandLine> options_adapter);
  bool isOk() override;
  llvm::Error getError() override;
  const std::vector<std::string> *getSourcePathList() override;
  clang::tooling::CompilationDatabase *getCompilations() override;
  bool isInplace() const override;

private:
  llvm::Expected<clang::tooling::CommonOptionsParser> expected_parser_;
}; // namespace FilesKeeper