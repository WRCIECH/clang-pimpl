#pragma once

#include "refactor_adapter/command_maps.hh"
#include "refactor_adapter/options_adapter.hh"
#include <iostream>

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

class ReorderFieldsOptionsAdapterForRegressionTests : public OptionsAdapter {
public:
  ~ReorderFieldsOptionsAdapterForRegressionTests() = default;
  ReorderFieldsOptionsAdapterForRegressionTests(std::string const &line);

  bool isInplace() const override { return true; }
  // Map creation needs to happen here as in constructor the category fields is
  // still not filled.
  CommandMaps const &getCommands() override;

private:
  std::string line_;
  std::vector<std::string> values;
  std::vector<std::vector<std::string>> elements;
};