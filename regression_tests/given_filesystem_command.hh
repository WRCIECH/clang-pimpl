#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilesystemCommand : public MetacommandExecutor {
public:
  GivenFilesystemCommand(FieldsOrderPack &state,
                         std::string const &main_directory)
      : MetacommandExecutor(state), main_directory_(main_directory) {

    llvm::sys::fs::current_path(testing_project_directory_);
    testing_project_directory_.append({"/", main_directory_});
  }

  void execute(std::string const &content) override {
    auto result = llvm::sys::fs::create_directory(testing_project_directory_);
    state_.all_files = generateListOfFiles(content);
    std::cout << "GivenFilesystemCommand: " << std::endl;
    for (auto f : state_.all_files) {
      createFile(f);
    }
  }

  void createFile(std::string const &file_name) {
    auto path_to_file{testing_project_directory_};
    path_to_file.append({"/", file_name});
    std::cout << "generates file in position " << path_to_file.c_str()
              << std::endl;
    int file_succeeded{0};
    auto op_result =
        llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);

    // Fill:
    state_.source_path_list.emplace_back(path_to_file.c_str());
    state_.all_files.emplace_back(file_name);
    state_.file_name_to_path[file_name] = path_to_file.c_str();
    clang::tooling::CompileCommand compile_command(
        testing_project_directory_.c_str(), path_to_file.c_str(),
        {"/usr/bin/c++", "-o", "CMakeFiles/test_app.dir/main.cc.o", "-c",
         path_to_file.c_str()},
        "");
    state_.compile_commands.emplace_back(std::move(compile_command));
  }

  std::vector<std::string> generateListOfFiles(std::string const &content) {
    std::stringstream ss{content};
    std::vector<std::string> result;
    std::copy(std::istream_iterator<std::string>(ss), {},
              std::back_inserter(result));
    return result;
  }

  void clear() override {
    llvm::sys::fs::remove_directories(testing_project_directory_);
  }

private:
  std::string main_directory_;
  llvm::SmallString<128> testing_project_directory_;
};
