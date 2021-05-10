#pragma once

#include "definitions_mover_action.hh"
#include "refactor_adapter/files_keeper.hh"
#include "refactor_adapter/refactor_adapter.hh"
#include "clang/Tooling/Refactoring.h"
#include <iostream>
#include <memory>
#include <vector>

class DefinitionsMoverRefactorAdapter : public RefactorAdapter {
public:
  std::unique_ptr<clang::tooling::FrontendActionFactory>
  createFrontendFactory(CommandMaps const &commands) override;

private:
  std::unique_ptr<clang::DefinitionsMoverAction> action_;
};