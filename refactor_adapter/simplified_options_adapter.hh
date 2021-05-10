#pragma once

#include "options_adapter.hh"
#include "refactor_adapter/command_maps.hh"
#include <iostream>

class SimplifiedOptionsAdapter : public OptionsAdapter {
public:
  ~SimplifiedOptionsAdapter() = default;
  SimplifiedOptionsAdapter(std::string const &line);

  bool isInplace() const override { return true; }
  CommandMaps const &getCommands() override;

private:
  std::string line_;
  std::vector<std::string> values;
  std::vector<std::vector<std::string>> elements;
};