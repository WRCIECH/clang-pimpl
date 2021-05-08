#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class FilestructureCommand : public MetacommandExecutor {
public:
  using ParsingResult =
      std::pair<std::vector<std::string>, std::map<std::string, std::string>>;

  FilestructureCommand(CompilationPack *state,
                       std::string const &test_directory_name)
      : MetacommandExecutor(state) {

    llvm::sys::fs::current_path(testing_project_directory_);
    testing_project_directory_.append({"/", test_directory_name});
  }
  ~FilestructureCommand() = default;

  std::string generateShortPath(
      std::string const &file_name,
      std::map<std::string, std::string> const &connections) const {
    std::vector<std::string> parts;

    auto it = connections.find(file_name);
    while (it != connections.end() && it->second != "[root]") {
      parts.push_back(it->second);
      it = connections.find(it->second);
    }
    std::string result;
    for (auto cit = parts.rbegin(); cit != parts.rend(); ++cit) {
      result += *cit;
      result += std::string("/");
    }
    if (!result.empty()) {
      result.pop_back();
    }
    return result;
  }

  ParsingResult generateListOfFiles(std::string const &content) {
    std::stringstream ss{content};
    int current_indent{-1};
    std::stack<std::string> dirs_stack;
    dirs_stack.push("[root]");
    std::map<std::string, std::string> connections;

    std::string line;
    while (std::getline(ss, line, '\n')) {
      int indent = line.find_first_not_of(' ');
      std::string s{line.begin() + line.find_first_not_of(' '), line.end()};
      if (indent < current_indent) {
        dirs_stack.pop();
        connections[s] = dirs_stack.top();
      } else if (indent > current_indent) {
        connections[s] = dirs_stack.top();
      } else {
        dirs_stack.pop();
        connections[s] = dirs_stack.top();
      }
      dirs_stack.push(s);
      current_indent = indent;
    }

    std::vector<std::string> result;
    for (auto const &[key, value] : connections) {
      std::string_view vkey(key);
      if (vkey.find('.') != std::string_view::npos) {
        result.push_back(key);
      }
    }
    return {result, connections};
  }

protected:
  static constexpr int MAX_STRING_SIZE{256};
  llvm::SmallString<MAX_STRING_SIZE> testing_project_directory_;
};