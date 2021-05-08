#pragma once

#include "refactor_adapter/command_maps.hh"
#include "refactor_adapter/options_adapter.hh"
#include <iostream>

class ReorderFieldsOptionsAdapterForRegressionTests : public OptionsAdapter {
public:
  ~ReorderFieldsOptionsAdapterForRegressionTests() = default;
  ReorderFieldsOptionsAdapterForRegressionTests(std::string const &line);

  bool isInplace() const override { return true; }
  CommandMaps const &getCommands() override;

private:
  std::string line_;
  std::vector<std::string> values;
  std::vector<std::vector<std::string>> elements;
};