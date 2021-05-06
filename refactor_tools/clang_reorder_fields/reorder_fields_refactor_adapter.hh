#pragma once

#include "refactor_adapter/files_keeper.hh"
#include "refactor_adapter/refactor_adapter.hh"
#include "reorder_fields_action.hh"
#include "clang/Tooling/Refactoring.h"
#include <iostream>
#include <memory>
#include <vector>

class ReorderFieldsRefactorAdapter : public RefactorAdapter {
public:
  std::unique_ptr<clang::tooling::FrontendActionFactory>
  createFrontendFactory(CommandMaps const &commands) override;

private:
  std::unique_ptr<clang::reorder_fields::ReorderFieldsAction> action_;
};