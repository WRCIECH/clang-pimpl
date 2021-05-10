#include "definitions_mover_action.hh"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"
#include "clang/Tooling/Refactoring.h"
#include "llvm/ADT/SetVector.h"
#include <algorithm>
#include <string>

namespace clang {
using namespace clang::ast_matchers;
std::unique_ptr<ASTConsumer> DefinitionsMoverAction::newASTConsumer() {
  return nullptr;
}

} // namespace clang
