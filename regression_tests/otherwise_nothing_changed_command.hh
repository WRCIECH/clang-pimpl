#pragma once

#include "filestructure_command.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>
#include <filesystem>

class OtherwiseNothingChangedCommand : public FilestructureCommand {
public:
  OtherwiseNothingChangedCommand(CompilationPack *state,
                                 std::string const &test_directory_name)
      : FilestructureCommand(state, test_directory_name) {}
  ~OtherwiseNothingChangedCommand() = default;

  int execute(std::string const &content) override {
    return filestructureNotChangedOrChecked() + filesNotChangedOrChecked();
  }

  int filestructureNotChangedOrChecked() {
    if (state_->filestructure_checked) {
      return 0;
    }

    std::string output{};
    for (auto entry = std::filesystem::recursive_directory_iterator(
             testing_project_directory_.c_str());
         entry != std::filesystem::recursive_directory_iterator(); ++entry) {
      output += std::string(entry.depth() * 2, ' ') +
                entry->path().filename().string() + std::string("\n");
    }

    auto result_files_map = generateListOfFiles(output).second;

    if (!mapsAreEqual(state_->initial_files_map, result_files_map)) {
      std::cerr << "Initial and result filestrucutres are not equal!\n";
      return -1;
    }
    return 0;
  }
  int filesNotChangedOrChecked() {
    for (auto entry = std::filesystem::recursive_directory_iterator(
             testing_project_directory_.c_str());
         entry != std::filesystem::recursive_directory_iterator(); ++entry) {
      if (!entry->path().extension().empty()) {
        auto filename = entry->path().filename().string();
        if (state_->filenameNotChecked(filename)) {

          auto file_path = state_->findPath(filename);
          if (file_path.empty()) {
            std::cerr << "Otherwise nothing changed command: " << filename
                      << "file was not found !!! \n";
            return -1;
          }
          std::ifstream modified_file{file_path};
          std::stringstream modified_content;
          modified_content << modified_file.rdbuf();
          auto content = modified_content.str();
          if (content != state_->file_content_map[filename]) {
            std::cerr << filename
                      << " was not checked but was modified. Initially: "
                      << state_->file_content_map[filename]
                      << ", but found: " << content << std::endl;
            return -1;
          }
        }
      }
      // TODO: verify if nothing was removed!
    }
    return 0;
  }
};
