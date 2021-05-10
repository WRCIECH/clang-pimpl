#include "definitions_mover_refactor_adapter.hh"
#include "clang/Tooling/Refactoring.h"

std::unique_ptr<clang::tooling::FrontendActionFactory>
DefinitionsMoverRefactorAdapter::createFrontendFactory(
    CommandMaps const &commands) {
  action_ = std::make_unique<clang::DefinitionsMoverAction>(
      commands.string_map.at("class-name"), tool_->getReplacements());

  return clang::tooling::newFrontendActionFactory(action_.get());
}