#include "refactor_adapter.hh"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include <iostream>

using namespace llvm;
using namespace clang;

int RefactorAdapter::parseArguments(std::unique_ptr<FilesKeeper> files_keeper) {
  files_keeper_ = std::move(files_keeper);

  if (!files_keeper_->isOk()) {
    llvm::errs() << files_keeper_->getError();
    return -1;
  }

  tool_ = std::make_unique<tooling::RefactoringTool>(
      *files_keeper_->getCompilations(), *files_keeper_->getSourcePathList());
  return 0;
}

int RefactorAdapter::performRefactoring() {
  auto factory = createFrontendFactory(files_keeper_->getCommands());

  if (files_keeper_->isInplace()) {
    return tool_->runAndSave(factory.get());
  }

  return performDryRunRefactoring(factory.get());
}

int RefactorAdapter::performDryRunRefactoring(
    clang::tooling::FrontendActionFactory *factory) {
  int exit_code = tool_->run(factory);

  LangOptions default_language_options;
  IntrusiveRefCntPtr<DiagnosticOptions> diagnostic_options(
      new DiagnosticOptions());
  TextDiagnosticPrinter diagnostic_printer(errs(), &*diagnostic_options);
  DiagnosticsEngine diagnostics(
      IntrusiveRefCntPtr<DiagnosticIDs>(new DiagnosticIDs()),
      &*diagnostic_options, &diagnostic_printer, false);

  auto &file_manager = tool_->getFiles();
  SourceManager sources(diagnostics, file_manager);
  Rewriter rewriter(sources, default_language_options);
  tool_->applyAllReplacements(rewriter);

  for (const auto &file : *files_keeper_->getSourcePathList()) {
    auto entry = file_manager.getFile(file);
    const auto id = sources.getOrCreateFileID(*entry, SrcMgr::C_User);

    rewriter.getEditBuffer(id).write(llvm::outs());
  }

  return exit_code;
}
