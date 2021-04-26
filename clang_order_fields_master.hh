#pragma once

#include "files_keeper.hh"
#include "clang/Tooling/Refactoring.h"
#include <memory>
#include <vector>

namespace clang {
namespace tooling {
class FrontendActionFactory;
} // namespace tooling
} // namespace clang

class ClangOrderFieldsMaster {
public:
  int parseArguments(std::unique_ptr<FilesKeeper> files_keeper);
  int performRefactoring();
  int performDryRunRefactoring(clang::tooling::FrontendActionFactory *factory);

private:
  std::unique_ptr<clang::tooling::RefactoringTool> tool_;
  std::unique_ptr<FilesKeeper> files_keeper_;
};