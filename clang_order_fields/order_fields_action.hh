//===-- tools/extra/clang-reorder-fields/ReorderFieldsAction.h -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declarations of the ReorderFieldsAction class and
/// the FieldPosition struct.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "clang/Tooling/Refactoring.h"

namespace clang {
class ASTConsumer;

namespace reorder_fields {

class ReorderFieldsAction {
  llvm::StringRef RecordName;
  llvm::ArrayRef<std::string> DesiredFieldsOrder;
  std::map<std::string, tooling::Replacements> &Replacements;

public:
  ReorderFieldsAction(
      llvm::StringRef RecordName,
      llvm::ArrayRef<std::string> DesiredFieldsOrder,
      std::map<std::string, tooling::Replacements> &Replacements)
      : RecordName(RecordName), DesiredFieldsOrder(DesiredFieldsOrder),
        Replacements(Replacements) {}

  ReorderFieldsAction(const ReorderFieldsAction &) = delete;
  ReorderFieldsAction &operator=(const ReorderFieldsAction &) = delete;

  std::unique_ptr<ASTConsumer> newASTConsumer();
};
} // namespace reorder_fields
} // namespace clang
