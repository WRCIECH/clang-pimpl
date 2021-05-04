#pragma once

#include "metacommand.hh"
#include "llvm/Support/FileSystem.h"
#include <algorithm>

class GivenFilestructureCommand : public MetacommandExecutor {
public:
  GivenFilestructureCommand(CompilationPack *state,
                            std::string const &test_directory_name)
      : MetacommandExecutor(state) {

    llvm::sys::fs::current_path(testing_project_directory_);
    testing_project_directory_.append({"/", test_directory_name});
  }
  ~GivenFilestructureCommand() = default;

  int execute(std::string const &content) override {
    state_->all_files = generateListOfFiles(content);
    for (auto const &f : state_->all_files) {
      createFile(f);
    }
    return 0;
  }

  std::string generateShortPath(std::string const &file_name) const {
    std::vector<std::string> parts;

    auto it = connections_.find(file_name);
    while (it != connections_.end() && it->second != "[root]") {
      parts.push_back(it->second);
      it = connections_.find(it->second);
    }
    std::string result;
    for (auto cit = parts.rbegin(); cit != parts.rend(); ++cit) {
      result += *cit;
      result += std::string("/");
    }
    result.pop_back();
    return result;
  }

  void createFile(std::string const &file_name) {
    auto short_path_to_file = generateShortPath(file_name);

    auto path_to_directory{testing_project_directory_};
    path_to_directory.append({"/", short_path_to_file});
    auto result = llvm::sys::fs::create_directories(path_to_directory, false);
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
        {"/home/wojciech/libraries/llvm-project/build/bin/clang++", "-o",
         "-I/home/wojciech/libraries/llvm-project/clang/lib/Headers",
         "-I/usr/lib/gcc/x86_64-linux-gnu/10/include",
         "CMakeFiles/test_app.dir/main.cc.o", "-c", path_to_file.c_str()},
        "");
    state_->compile_commands.emplace_back(std::move(compile_command));
  }

  std::vector<std::string> generateListOfFiles(std::string const &content) {
    std::stringstream ss{content};
    int current_indent{-1};
    std::stack<std::string> dirs_stack;
    dirs_stack.push("[root]");

    std::string line;
    while (std::getline(ss, line, '\n')) {
      int indent = line.find_first_not_of(' ');
      std::string s{line.begin() + line.find_first_not_of(' '), line.end()};
      if (indent < current_indent) {
        dirs_stack.pop();
        connections_[s] = dirs_stack.top();
      } else if (indent > current_indent) {
        connections_[s] = dirs_stack.top();
      } else {
        dirs_stack.pop();
        connections_[s] = dirs_stack.top();
      }
      dirs_stack.push(s);
      current_indent = indent;
    }

    std::vector<std::string> result;
    for (auto const &[key, value] : connections_) {
      std::string_view vkey(key);
      if (vkey.find('.') != std::string_view::npos) {
        result.push_back(key);
      }
    }
    return result;
  }

private:
  llvm::SmallString<128> testing_project_directory_;
  std::map<std::string, std::string> connections_;
};
