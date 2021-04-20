#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilesystemCommand : public MetacommandExecutor {
public:
  GivenFilesystemCommand(std::string const &main_directory)
      : main_directory_(main_directory) {}

  void execute(std::string const &content) override {
    llvm::SmallString<128> current_dir;
    llvm::sys::fs::current_path(current_dir);
    current_dir.append({"/", main_directory_});
    auto result = llvm::sys::fs::create_directory(current_dir);
    auto list_of_files = generateListOfFiles(content);
    std::cout << "GivenFilesystemCommand: " << std::endl;
    for (auto f : list_of_files) {
      auto path_to_file{current_dir};
      path_to_file.append({"/", f});
      std::cout << "generates file in position " << path_to_file.c_str()
                << std::endl;
      int file_succeeded{0};
      auto op_result =
          llvm::sys::fs::openFileForWrite(path_to_file, file_succeeded);
    }
  }

  std::vector<std::string> generateListOfFiles(std::string const &content) {
    std::stringstream ss{content};
    std::vector<std::string> result;
    std::copy(std::istream_iterator<std::string>(ss), {},
              std::back_inserter(result));
    return result;
  }

private:
  std::string main_directory_;
};
