#include "command_line_files_keeper.hh"
#include <iostream>

using namespace llvm;
using namespace clang;

CommandLineFilesKeeper::CommandLineFilesKeeper(
    int argc, const char **argv,
    std::shared_ptr<OptionsAdapterForCommandLine> options_adapter)
    : FilesKeeper(options_adapter),
      expected_parser_(tooling::CommonOptionsParser::create(
          argc, argv, options_adapter->getOptionsCategory(),
          options_adapter->getNumOccurencesFlag(),
          options_adapter->getUsage())) {}

std::unique_ptr<CommandLineFilesKeeper> CommandLineFilesKeeper::create(
    int argc, const char **argv,
    std::shared_ptr<OptionsAdapterForCommandLine> options_adapter) {
  return std::make_unique<CommandLineFilesKeeper>(argc, argv,
                                                  std::move(options_adapter));
}

bool CommandLineFilesKeeper::isOk() {
  if (expected_parser_) {
    return true;
  }
  return false;
}
llvm::Error CommandLineFilesKeeper::getError() {
  return expected_parser_.takeError();
}

const std::vector<std::string> *CommandLineFilesKeeper::getSourcePathList() {
  return &expected_parser_.get().getSourcePathList();
}

clang::tooling::CompilationDatabase *CommandLineFilesKeeper::getCompilations() {
  return &expected_parser_.get().getCompilations();
}

bool CommandLineFilesKeeper::isInplace() const {
  return options_adapter_->isInplace();
}