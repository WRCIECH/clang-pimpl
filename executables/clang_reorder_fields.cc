#include "refactor_adapter/command_line_files_keeper.hh"
#include "refactor_tools/clang_reorder_fields/reorder_fields_refactor_adapter.hh"

class ReorderFieldsOptionsAdapterForCommandLine
    : public OptionsAdapterForCommandLine {
public:
  ~ReorderFieldsOptionsAdapterForCommandLine() = default;
  ReorderFieldsOptionsAdapterForCommandLine();

  llvm::cl::OptionCategory &getOptionsCategory() override {
    return clang_reorder_fields_category_;
  }
  llvm::cl::NumOccurrencesFlag getNumOccurencesFlag() override {
    return llvm::cl::OneOrMore;
  }
  const char *getUsage() override { return usage_.c_str(); }

  bool isInplace() const override { return inplace_; }

  // Map creation needs to happen here as in constructor the category fields is
  // still not filled.
  CommandMaps const &getCommands() override;

private:
  llvm::cl::opt<std::string> record_name_;
  llvm::cl::list<std::string> fields_order_;
  llvm::cl::opt<bool> inplace_;
  llvm::cl::OptionCategory clang_reorder_fields_category_;
  std::string usage_;
};

ReorderFieldsOptionsAdapterForCommandLine::
    ReorderFieldsOptionsAdapterForCommandLine()
    : record_name_{"record-name", llvm::cl::Required,
                   llvm::cl::desc("The name of the struct/class."),
                   llvm::cl::cat(clang_reorder_fields_category_)},
      fields_order_{"fields-order", llvm::cl::CommaSeparated,
                    llvm::cl::OneOrMore,
                    llvm::cl::desc("The desired fields order."),
                    llvm::cl::cat(clang_reorder_fields_category_)},
      clang_reorder_fields_category_{"clang-reorder-fields options"},
      usage_{"A tool to reorder fields in C/C++ structs/classes.\n"},
      inplace_{"i", llvm::cl::desc("Overwrite edited files.")} {}

// Map creation needs to happen here as in constructor the category fields is
// still not filled.
CommandMaps const &ReorderFieldsOptionsAdapterForCommandLine::getCommands() {
  command_maps_.string_map["record-name"] = record_name_;
  command_maps_.array_map["fields-order"] = fields_order_;
  return command_maps_;
}

int main(int argc, const char **argv) {
  std::unique_ptr<RefactorAdapter> m =
      std::make_unique<ReorderFieldsRefactorAdapter>();
  auto parsing_result = m->parseArguments(CommandLineFilesKeeper::create(
      argc, argv,
      std::make_shared<ReorderFieldsOptionsAdapterForCommandLine>()));
  if (parsing_result) {
    return -1;
  }
  return m->performRefactoring();
}
