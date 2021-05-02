#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilestructureCommand : public MetacommandExecutor {
public:
  GivenFilestructureCommand(CompilationPack &state,
                            std::string const &test_directory_name,
                            std::string const &main_directory)
      : MetacommandExecutor(state),
        main_directory_(test_directory_name + std::string("/") +
                        main_directory) {

    llvm::sys::fs::current_path(testing_project_directory_);
    testing_project_directory_.append({"/", main_directory_});
  }

  int execute(std::string const &content) override {
    auto result = llvm::sys::fs::create_directory(testing_project_directory_);
    std::cout << content << std::endl << std::endl;
    state_.all_files = generateListOfFiles(content);
    for (auto const &f : state_.all_files) {
      createFile(f);
    }
    return 0;
  }

  void createFile(std::string const &file_name) {
    auto path_to_file{testing_project_directory_};
    path_to_file.append({"/", file_name});
    int file_succeeded{0};
    auto op_result =
        llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);

    state_.source_path_list.emplace_back(path_to_file.c_str());
    state_.file_name_to_path[file_name] = path_to_file.c_str();
    clang::tooling::CompileCommand compile_command(
        testing_project_directory_.c_str(), path_to_file.c_str(),
        {"/home/wojciech/libraries/llvm-project/build/bin/clang++", "-o",
         "-I/home/wojciech/libraries/llvm-project/clang/lib/Headers",
         "-I/usr/lib/gcc/x86_64-linux-gnu/10/include",
         "CMakeFiles/test_app.dir/main.cc.o", "-c", path_to_file.c_str()},
        "");
    state_.compile_commands.emplace_back(std::move(compile_command));
  }

  std::vector<std::string> generateListOfFiles(std::string const &content) {
    std::stringstream ss{content};
    std::vector<std::string> result;
    std::copy_if(std::istream_iterator<std::string>(ss), {},
                 std::back_inserter(result),
                 [](auto const &v) { return !v.empty(); });
    return result;
  }

private:
  std::string main_directory_;
  llvm::SmallString<128> testing_project_directory_;
};
