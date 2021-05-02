#pragma once

#include "compilation_pack.hh"
#include "refactor_adapter/files_keeper.hh"
#include <memory>

class FilesKeeperForRegressionTests : public FilesKeeper {
public:
  FilesKeeperForRegressionTests(CompilationPack &pack);
  static std::unique_ptr<FilesKeeperForRegressionTests>
  create(CompilationPack &pack);
  bool isOk() override;
  llvm::Error getError() override;
  const std::vector<std::string> *getSourcePathList() override;
  clang::tooling::CompilationDatabase *getCompilations() override;
  bool isInplace() const override;

private:
  std::unique_ptr<clang::tooling::CompilationDatabase> compilation_database_;
  CompilationPack &pack_;
};