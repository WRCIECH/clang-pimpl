#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilesystemCommand : public MetacommandExecutor {
public:
  GivenFilesystemCommand(std::string const &main_directory)
      : main_directory_(main_directory) {

    llvm::sys::fs::current_path(testing_project_directory_);
    testing_project_directory_.append({"/", main_directory_});
  }

  void execute(std::string const &content) override {
    auto result = llvm::sys::fs::create_directory(testing_project_directory_);
    auto list_of_files = generateListOfFiles(content);
    std::cout << "GivenFilesystemCommand: " << std::endl;
    for (auto f : list_of_files) {
      createFile(f);
    }
    generateCmakeLists();
  }

  void createFile(std::string const &file_name) {
    auto path_to_file{testing_project_directory_};
    path_to_file.append({"/", file_name});
    std::cout << "generates file in position " << path_to_file.c_str()
              << std::endl;
    int file_succeeded{0};
    auto op_result =
        llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);
  }
  void generateCmakeLists() {
    auto path_to_file{testing_project_directory_};
    path_to_file.append({"/", "CMakeLists.txt"});
    std::cout << "generates file in position " << path_to_file.c_str()
              << std::endl;
    int file_succeeded{0};
    auto op_result =
        llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);
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
