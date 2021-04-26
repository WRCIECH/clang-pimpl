#pragma once

#include "fields_order_pack.hh"
#include "files_keeper.hh"
#include <memory>

class FilesKeeperForRegressionTests : public FilesKeeper {
public:
  FilesKeeperForRegressionTests(FieldsOrderPack const &pack);
  static std::unique_ptr<FilesKeeperForRegressionTests>
  create(FieldsOrderPack const &pack);
  bool isOk() override;
  llvm::Error getError() override;

  const std::vector<std::string> *getSourcePathList() override;

  clang::tooling::CompilationDatabase *getCompilations() override;

  llvm::StringRef getRecordName() const override;
  llvm::ArrayRef<std::string> getDesiredFieldsOrder() const override;
  bool isInplace() const override;

private:
  std::unique_ptr<clang::tooling::CompilationDatabase> compilation_database_;
  const FieldsOrderPack &pack_;
};