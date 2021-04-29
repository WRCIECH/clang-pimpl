#pragma once

#include "fields_order_pack.hh"
#include "files_keeper.hh"
#include <memory>

class FilesKeeperForRegressionTests : public FilesKeeper {
public:
  FilesKeeperForRegressionTests(FieldsOrderPack &pack);
  static std::unique_ptr<FilesKeeperForRegressionTests>
  create(FieldsOrderPack &pack);
  bool isOk() override;
  llvm::Error getError() override;

  const std::vector<std::string> *getSourcePathList() override;

  clang::tooling::CompilationDatabase *getCompilations() override;

  llvm::StringRef getRecordName() const override;
  llvm::ArrayRef<std::string> getDesiredFieldsOrder() const override;
  bool isInplace() const override;

  llvm::raw_ostream *
  getRawOstreamForFile(std::string const &file_name) override;

private:
  std::unique_ptr<clang::tooling::CompilationDatabase> compilation_database_;
  FieldsOrderPack &pack_;
};