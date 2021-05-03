#pragma once

#include "command_maps.hh"
#include "files_keeper.hh"
#include "clang/Tooling/Refactoring.h"
#include <memory>
#include <vector>

namespace clang {
namespace tooling {
class FrontendActionFactory;
} // namespace tooling
} // namespace clang
class RefactorAdapter {
public:
  virtual ~RefactorAdapter() = default;
  int parseArguments(std::unique_ptr<FilesKeeper> files_keeper);
  int performRefactoring();
  int performDryRunRefactoring(clang::tooling::FrontendActionFactory *factory);

  virtual std::unique_ptr<clang::tooling::FrontendActionFactory>
  createFrontendFactory(CommandMaps const &) = 0;

protected:
  std::unique_ptr<clang::tooling::RefactoringTool> tool_;
  std::unique_ptr<FilesKeeper> files_keeper_;
};