#include "regression_tests_parser.hh"

#include "execute_command.hh"
#include "expect_file_command.hh"
#include "given_file_command.hh"
#include "given_filesystem_command.hh"

#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>

RegressionTestsParser::RegressionTestsParser(
    std::string const &directory_location) {}

bool RegressionTestsParser::isCommentLine(std::string const &line_word) const {
  bool line_is_empty = line_word.empty();
  bool comment_string =
      (line_word.size() > 1) && (line_word.find("//") != std::string::npos);
  return line_is_empty || comment_string;
}

int RegressionTestsParser::parseFile(std::string const &file_location) {
  std::fstream file(file_location);

  if (!file.is_open()) {
    std::cerr << "File was not found [" << file_location << "]\n";
    return -1;
  }

  std::string line;
  size_t current_line_number{0u};
  std::string content{};
  bool requires_metacommand{true};
  std::vector<std::unique_ptr<MetacommandExecutor>> executors;
  FieldsOrderPack state;

  try {
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
      case Metacommand::GIVEN_FILESYSTEM:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<GivenFilesystemCommand>(state, result[0]));
        break;
      case Metacommand::GIVEN_FILE:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<GivenFileCommand>(state, result[0]));
        break;
      case Metacommand::EXECUTE:
        requires_metacommand = false;
        executors.emplace_back(std::make_unique<ExecuteCommand>(state));
        break;
      case Metacommand::EXPECT_FILE:
        requires_metacommand = false;
        executors.emplace_back(
            std::make_unique<ExpectFileCommand>(state, result[0]));
        break;
      case Metacommand::END:
        requires_metacommand = true;
        if (!content.empty()) {
          content.pop_back();
        }
        executors.back()->execute(std::exchange(content, ""));
        break;
      }
    }
  } catch (ParsingException const &e) {
    std::cerr << "in file: " << file_location << ", line "
              << current_line_number << ": " << std::quoted(line) << std::endl;
    std::cerr << e.what() << std::endl;
    return -1;
  }
  // std::for_each(executors.rbegin(), executors.rend(),
  //               [](auto &executor) { executor->clear(); });
  std::cout << "All good!\n";
  return 0;
}

std::optional<Metacommand>
RegressionTestsParser::determineMetacommand(std::string const &s) {
  if (s == "GIVEN_FILESYSTEM")
    return Metacommand::GIVEN_FILESYSTEM;
  if (s == "GIVEN_FILE")
    return Metacommand::GIVEN_FILE;
  if (s == "EXECUTE")
    return Metacommand::EXECUTE;
  if (s == "EXPECT_FILE")
    return Metacommand::EXPECT_FILE;
  if (s == "END")
    return Metacommand::END;

  return std::nullopt;
}

void RegressionTestsParser::executeCommand(
    std::deque<std::string> const &words) {
  // Execute!
}

ParsingException
RegressionTestsParser::generateError(std::string const &line,
                                     std::string const &error_ending) {
  std::stringstream error_message;
  error_message << std::quoted(line) << std::string(error_ending);
  error_message << "Error!\n";

  return ParsingException(error_message.str());
}