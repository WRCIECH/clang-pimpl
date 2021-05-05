#pragma once

#include "filestructure_command.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>
#include <filesystem>

template <typename Map> bool mapsAreEqual(Map const &lhs, Map const &rhs) {
  // No predicate needed because there is operator== for pairs already.
  return lhs.size() == rhs.size() &&
         std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

class ExpectFilestructureCommand : public FilestructureCommand {
public:
  ExpectFilestructureCommand(CompilationPack *state,
                             std::string const &test_directory_name)
      : FilestructureCommand(state, test_directory_name) {}
  ~ExpectFilestructureCommand() = default;

  int execute(std::string const &content) override {

    std::string output{};
    for (auto entry = std::filesystem::recursive_directory_iterator(
             testing_project_directory_.c_str());
         entry != std::filesystem::recursive_directory_iterator(); ++entry) {
      output += std::string(entry.depth() * 2, ' ') +
                entry->path().filename().string() + std::string("\n");
    }

    auto expected_files_map = generateListOfFiles(content).second;
    auto result_files_map = generateListOfFiles(output).second;

    if (!mapsAreEqual(expected_files_map, result_files_map)) {
      std::cerr << "Expected and result filestrucutres are not equal!\n";
      std::cerr << output << std::endl;
      std::cerr << content << std::endl;
      return -1;
    }

    return 0;
  }
};
