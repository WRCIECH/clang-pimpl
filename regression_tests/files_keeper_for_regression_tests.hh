#pragma once

#include "compilation_pack.hh"
#include "refactor_adapter/files_keeper.hh"
#include "clang/Tooling/CommonOptionsParser.h"
#include <memory>

class FilesKeeperForRegressionTests : public FilesKeeper {
public:
  FilesKeeperForRegressionTests(
      CompilationPack *pack, std::shared_ptr<OptionsAdapter> options_adapter);
  static std::unique_ptr<FilesKeeperForRegressionTests>
  create(CompilationPack *pack,
         std::shared_ptr<OptionsAdapter> options_adapter);
  bool isOk() override;
  llvm::Error getError() override;
  const std::vector<std::string> *getSourcePathList() override;
  clang::tooling::CompilationDatabase *getCompilations() override;
  bool isInplace() const override;

private:
  std::unique_ptr<clang::tooling::CompilationDatabase> compilation_database_;
  CompilationPack *pack_;
};