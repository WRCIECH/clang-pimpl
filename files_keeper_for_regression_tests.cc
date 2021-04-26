#include "files_keeper_for_regression_tests.hh"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

class CompilationDatabaseForRegressionTests
    : public clang::tooling::CompilationDatabase {
public:
  CompilationDatabaseForRegressionTests(FieldsOrderPack const &pack)
      : pack_(pack) {}

private:
  std::vector<clang::tooling::CompileCommand>
  getCompileCommands(llvm::StringRef FilePath) const override {
    return getAllCompileCommands();
  }

  std::vector<std::string> getAllFiles() const override {
    return pack_.all_files;
  }
  std::vector<clang::tooling::CompileCommand>
  getAllCompileCommands() const override {
    return pack_.compile_commands;
  }

private:
  const FieldsOrderPack &pack_;
};

FilesKeeperForRegressionTests::FilesKeeperForRegressionTests(
    FieldsOrderPack const &pack)
    : pack_(pack) {
  compilation_database_ =
      std::make_unique<CompilationDatabaseForRegressionTests>(pack_);
}

std::unique_ptr<FilesKeeperForRegressionTests>
FilesKeeperForRegressionTests::create(FieldsOrderPack const &pack) {
  return std::make_unique<FilesKeeperForRegressionTests>(pack);
}
bool FilesKeeperForRegressionTests::isOk() { return true; }
llvm::Error FilesKeeperForRegressionTests::getError() {
  return llvm::Error::success();
}

const std::vector<std::string> *
FilesKeeperForRegressionTests::getSourcePathList() {
  return &pack_.source_path_list;
}

clang::tooling::CompilationDatabase *
FilesKeeperForRegressionTests::getCompilations() {
  return compilation_database_.get();
}

llvm::StringRef FilesKeeperForRegressionTests::getRecordName() const {
  return pack_.record_name;
}
llvm::ArrayRef<std::string>
FilesKeeperForRegressionTests::getDesiredFieldsOrder() const {
  return pack_.fields_order;
}
bool FilesKeeperForRegressionTests::isInplace() const { return false; }