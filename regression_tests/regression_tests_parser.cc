#include "regression_tests_parser.hh"

#include "execute_command.hh"
#include "expect_file_command.hh"
#include "expect_filestructure_command.hh"
#include "given_file_command.hh"
#include "given_filestructure_command.hh"
#include "otherwise_nothing_changed_command.hh"

#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>

RegressionTestsParser::RegressionTestsParser(
    std::string const &directory_location)
    : test_directory_name_(directory_location) {}

std::vector<std::string> RegressionTestsParser::loadIncludeDirectories() {
  std::filesystem::path p{INCLUDE_DIRECTORIES_LOCATION};
  auto file_path = p / ".include-directories-for-regression-tests";
  std::fstream include_directories_for_regression_tests{file_path};
  if (!include_directories_for_regression_tests.is_open()) {
    std::cerr << file_path.string()
              << " file is not defined. Define it and provide paths to local "
                 "stl library and {path_to_llvm_project}/clang/lib/Headers "
                 "directories\n";
    return {};
  }
  std::vector<std::string> result;
  std::copy(
      std::istream_iterator<std::string>{
          include_directories_for_regression_tests},
      {}, std::back_inserter(result));
  return result;
}

int RegressionTestsParser::parseFile(std::string const &file_location) {
  std::fstream file(file_location);
  int tests_result{0};

  if (!file.is_open()) {
    std::cerr << "File was not found [" << file_location << "]\n";
    return -1;
  }

  std::string line;
  size_t current_line_number{0u};
  try {
    std::string content{};
    bool requires_metacommand{true};
    std::vector<std::unique_ptr<MetacommandExecutor>> executors;
    auto include_directories = loadIncludeDirectories();
    if (include_directories.empty()) {
      return -1;
    }
    auto state = std::make_unique<CompilationPack>(std::move(include_directories));
    while (std::getline(file, line)) {
      ++current_line_number;
      std::deque<std::string> result;
      boost::split(result, line, boost::is_any_of(" "));
      if (isCommentLine(line)) {
        continue;
      }
      auto metacommand = determineMetacommand(result[0]);
      if (!metacommand.has_value()) {
        if (!requires_metacommand) {
          content += line + "\n";
          continue;
        } else {
          throw generateError(line, " metacommand unrecognized but required ");
        }
      }
      result.pop_front();
      switch (*metacommand) {
      case Metacommand::GIVEN_FILESTRUCTURE:
        requires_metacommand = false;
        executors.emplace_back(std::make_unique<GivenFilestructureCommand>(
            state.get(), test_directory_name_));
        break;
      case Metacommand::GIVEN_FILE:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<GivenFileCommand>(state.get(), result[0]));
        break;
      case Metacommand::EXECUTE:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<ExecuteCommand>(state.get(), result[0]));
        break;
      case Metacommand::EXPECT_FILE:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<ExpectFileCommand>(state.get(), result[0]));
        break;
      case Metacommand::EXPECT_FILESTRUCTURE:
        requires_metacommand = false;
        executors.emplace_back(std::make_unique<ExpectFilestructureCommand>(
            state.get(), test_directory_name_));
        break;
      case Metacommand::END:
        requires_metacommand = true;
        if (!content.empty()) {
          content.pop_back();
        }
        tests_result = executors.back()->execute(std::exchange(content, ""));
        if (tests_result != 0) {
          return tests_result;
        }
        break;
      }
    }
    auto last_command = std::make_unique<OtherwiseNothingChangedCommand>(
        state.get(), test_directory_name_);
    tests_result = last_command->execute("");
    if (tests_result != 0) {
      return tests_result;
    }
  } catch (ParsingException const &e) {
    std::cerr << "in file: " << file_location << ", line "
              << current_line_number << ": " << std::quoted(line) << std::endl;
    std::cerr << e.what() << std::endl;
    return -1;
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  std::cout << "Tests result " << tests_result << std::endl;
  return tests_result;
}

std::optional<Metacommand>
RegressionTestsParser::determineMetacommand(std::string const &s) {
  if (s == "GIVEN_FILESTRUCTURE")
    return Metacommand::GIVEN_FILESTRUCTURE;
  if (s == "GIVEN_FILE")
    return Metacommand::GIVEN_FILE;
  if (s == "EXECUTE")
    return Metacommand::EXECUTE;
  if (s == "EXPECT_FILE")
    return Metacommand::EXPECT_FILE;
  if (s == "EXPECT_FILESTRUCTURE")
    return Metacommand::EXPECT_FILESTRUCTURE;
  if (s == "END")
    return Metacommand::END;

  return std::nullopt;
}

ParsingException
RegressionTestsParser::generateError(std::string const &line,
                                     std::string const &error_ending) {
  std::stringstream error_message;
  error_message << std::quoted(line) << std::string(error_ending);
  error_message << "Error!\n";

  return ParsingException(error_message.str());
}

bool RegressionTestsParser::isCommentLine(std::string const &line_word) const {
  bool line_is_empty = line_word.empty();
  bool comment_string =
      (line_word.size() > 1) && (line_word.find("//") != std::string::npos);
  return line_is_empty || comment_string;
}
