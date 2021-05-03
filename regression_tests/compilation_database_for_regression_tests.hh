#include "files_keeper_for_regression_tests.hh"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

class CompilationDatabaseForRegressionTests
    : public clang::tooling::CompilationDatabase {
public:
  CompilationDatabaseForRegressionTests(CompilationPack *pack) : pack_(pack) {}

private:
  std::vector<clang::tooling::CompileCommand>
  getCompileCommands(llvm::StringRef FilePath) const override {
    return getAllCompileCommands();
  }

  std::vector<std::string> getAllFiles() const override {
    return pack_->all_files;
  }
  std::vector<clang::tooling::CompileCommand>
  getAllCompileCommands() const override {
    return pack_->compile_commands;
  }

private:
  const CompilationPack *pack_;
};