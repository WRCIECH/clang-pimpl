#include "reorder_fields_refactor_adapter.hh"
#include "clang/Tooling/Refactoring.h"

std::unique_ptr<clang::tooling::FrontendActionFactory>
ReorderFieldsRefactorAdapter::createFrontendFactory(
    CommandMaps const &commands) {
  // TODO: protect against exceptions!

  action_ = std::make_unique<clang::reorder_fields::ReorderFieldsAction>(
      commands.string_map.at("record-name"),
      commands.array_map.at("fields-order"), tool_->getReplacements());

  return clang::tooling::newFrontendActionFactory(action_.get());
}