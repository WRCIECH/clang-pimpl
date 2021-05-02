#include "command_line_files_keeper.hh"
#include <iostream>

using namespace llvm;
using namespace clang;

CommandLineFilesKeeper::CommandLineFilesKeeper(
    llvm::Expected<clang::tooling::CommonOptionsParser> &&p)
    : expected_parser_(std::move(p)) {}

std::unique_ptr<CommandLineFilesKeeper>
CommandLineFilesKeeper::create(int argc, const char **argv) {
  return std::make_unique<CommandLineFilesKeeper>(
      tooling::CommonOptionsParser::create(argc, argv,
                                           clang_reorder_fields_category_,
                                           cl::OneOrMore, usage_.c_str()));

  // TODO: generate_commands_here !;
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

bool CommandLineFilesKeeper::isInplace() const { return inplace_; }

cl::opt<std::string> CommandLineFilesKeeper::record_name_{
    "record-name", cl::Required, cl::desc("The name of the struct/class."),
    cl::cat(clang_reorder_fields_category_)};
cl::list<std::string> CommandLineFilesKeeper::fields_order_{
    "fields-order", cl::CommaSeparated, cl::OneOrMore,
    cl::desc("The desired fields order."),
    cl::cat(clang_reorder_fields_category_)};
cl::OptionCategory CommandLineFilesKeeper::clang_reorder_fields_category_{
    "clang-reorder-fields options"};
std::string CommandLineFilesKeeper::usage_{
    "A tool to reorder fields in C/C++ structs/classes.\n"};
cl::opt<bool> CommandLineFilesKeeper::inplace_{
    "i", cl::desc("Overwrite edited files."),
    cl::cat(clang_reorder_fields_category_)};