#pragma once

#include "filestructure_command.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilestructureCommand : public FilestructureCommand {
public:
  GivenFilestructureCommand(CompilationPack *state,
                            std::string const &test_directory_name)
      : FilestructureCommand(state, test_directory_name) {}
  ~GivenFilestructureCommand() = default;

  int execute(std::string const &content) override {
    state_->all_files = generateListOfFiles(content).first;
    state_->initial_files_map = generateListOfFiles(content).second;
    for (auto const &f : state_->all_files) {
      auto short_path_to_file = generateShortPath(f, state_->initial_files_map);
      createFile(f, short_path_to_file);
    }
    return 0;
  }

  void createFile(std::string const &file_name,
                  std::string const &short_path_to_file) {

    auto path_to_directory{testing_project_directory_};
    if (!short_path_to_file.empty()) {
      path_to_directory.append({"/", short_path_to_file});
      auto result = llvm::sys::fs::create_directories(path_to_directory, false);
    }
    int file_succeeded{0};
    auto path_to_file{path_to_directory};
    path_to_file.append({"/", file_name});

    auto op_result =
        llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);
    if (op_result) {
      std::stringstream error_message;
      error_message << "Error in createFilestructure: ";
      error_message << path_to_file.c_str() << ". Error: ";
      error_message << op_result.message();
      throw ParsingException(error_message.str());
    }
    state_->source_path_list.emplace_back(path_to_file.c_str());
    clang::tooling::CompileCommand compile_command(
        testing_project_directory_.c_str(), path_to_file.c_str(),
        // change!
        {"/home/wojciech/libraries/llvm-project/build/bin/clang++", "-o",
         "-I/home/wojciech/libraries/llvm-project/clang/lib/Headers",
         "-I/usr/lib/gcc/x86_64-linux-gnu/10/include",
         "CMakeFiles/test_app.dir/main.cc.o", "-c", path_to_file.c_str()},
        "");
    state_->compile_commands.emplace_back(std::move(compile_command));
  }
};
