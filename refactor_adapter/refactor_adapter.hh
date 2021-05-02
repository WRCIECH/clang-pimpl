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

class RefactorAdapter {
public:
  virtual ~RefactorAdapter() = default;
  int parseArguments(std::unique_ptr<FilesKeeper> files_keeper);
  int performRefactoring(
      std::map<std::string, std::vector<std::string>> const &);
  int performDryRunRefactoring(clang::tooling::FrontendActionFactory *factory);

  virtual std::unique_ptr<clang::tooling::FrontendActionFactory>
  createFrontendFactory(
      std::map<std::string, std::vector<std::string>> const &commands) = 0;

protected:
  std::unique_ptr<clang::tooling::RefactoringTool> tool_;
  std::unique_ptr<FilesKeeper> files_keeper_;
};
