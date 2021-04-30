#pragma once

#include "../files_keeper.hh"
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
      llvm::Expected<clang::tooling::CommonOptionsParser> &&p);

  static std::unique_ptr<CommandLineFilesKeeper> create(int argc,
                                                        const char **argv);
  bool isOk() override;
  llvm::Error getError() override;

  const std::vector<std::string> *getSourcePathList() override;

  clang::tooling::CompilationDatabase *getCompilations() override;

  llvm::StringRef getRecordName() const override;
  llvm::ArrayRef<std::string> getDesiredFieldsOrder() const override;
  bool isInplace() const override;

private:
  static llvm::cl::opt<std::string> record_name_;
  static llvm::cl::list<std::string> fields_order_;
  static llvm::cl::opt<bool> inplace_;
  static llvm::cl::OptionCategory clang_reorder_fields_category_;
  static std::string usage_;
  llvm::Expected<clang::tooling::CommonOptionsParser> expected_parser_;
}; // namespace FilesKeeper