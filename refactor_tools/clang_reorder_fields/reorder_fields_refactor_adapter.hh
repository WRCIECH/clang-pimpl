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
  std::unique_ptr<clang::tooling::FrontendActionFactory> createFrontendFactory(
      std::map<std::string, std::vector<std::string>> const &commands)
      override {

    if (commands.count("record-name") > 0) {
      record_name = commands.at("record-name")[0];
    } else {
      std::cout << "record-name command not recognized\n";
    }
    if (commands.count("fields-order") > 0) {
      fields_order = commands.at("fields-order");
    } else {
      std::cout << "fields-order command not recognized\n";
    }

    action_ = std::make_unique<clang::reorder_fields::ReorderFieldsAction>(
        record_name, fields_order, tool_->getReplacements());

    return clang::tooling::newFrontendActionFactory(action_.get());
  }

private:
  std::unique_ptr<clang::reorder_fields::ReorderFieldsAction> action_;

  std::string record_name;
  std::vector<std::string> fields_order;
};