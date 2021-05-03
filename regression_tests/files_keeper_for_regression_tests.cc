#include "files_keeper_for_regression_tests.hh"
#include "compilation_database_for_regression_tests.hh"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

FilesKeeperForRegressionTests::FilesKeeperForRegressionTests(
    CompilationPack *pack, std::shared_ptr<OptionsAdapter> options_adapter)
    : FilesKeeper(std::move(options_adapter)), pack_(pack) {
  compilation_database_ =
      std::make_unique<CompilationDatabaseForRegressionTests>(pack_);
}

std::unique_ptr<FilesKeeperForRegressionTests>
FilesKeeperForRegressionTests::create(
    CompilationPack *pack, std::shared_ptr<OptionsAdapter> options_adapter) {
  return std::make_unique<FilesKeeperForRegressionTests>(
      pack, std::move(options_adapter));
}
bool FilesKeeperForRegressionTests::isOk() { return true; }
llvm::Error FilesKeeperForRegressionTests::getError() {
  return llvm::Error::success();
}

const std::vector<std::string> *
FilesKeeperForRegressionTests::getSourcePathList() {
  return &pack_->source_path_list;
}

clang::tooling::CompilationDatabase *
FilesKeeperForRegressionTests::getCompilations() {
  return compilation_database_.get();
}

// Overwrites to true even if options doesn't specify it.
bool FilesKeeperForRegressionTests::isInplace() const { return true; }