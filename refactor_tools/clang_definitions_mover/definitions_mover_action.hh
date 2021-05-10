#pragma once

#include "clang/Tooling/Refactoring.h"

namespace clang {
class ASTConsumer;

class DefinitionsMoverAction {
  std::map<std::string, tooling::Replacements> &Replacements;

public:
  DefinitionsMoverAction(
      llvm::StringRef RecordName,
      std::map<std::string, tooling::Replacements> &Replacements)
      : Replacements(Replacements) {}

  DefinitionsMoverAction(const DefinitionsMoverAction &) = delete;
  DefinitionsMoverAction &operator=(const DefinitionsMoverAction &) = delete;

  std::unique_ptr<ASTConsumer> newASTConsumer();
};
} // namespace clang