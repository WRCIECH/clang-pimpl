#pragma once

class OptionsAdapter {
public:
  virtual ~OptionsAdapter() = default;
  virtual bool isInplace() const = 0;
  virtual CommandMaps const &getCommands() = 0;

protected:
  CommandMaps command_maps_;
};

class OptionsAdapterForCommandLine : public OptionsAdapter {
public:
  virtual ~OptionsAdapterForCommandLine() = default;
  virtual llvm::cl::OptionCategory &getOptionsCategory() = 0;
  virtual llvm::cl::NumOccurrencesFlag getNumOccurencesFlag() = 0;
  virtual const char *getUsage() = 0;
};
