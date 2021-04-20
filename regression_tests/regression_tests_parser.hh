#pragma once

#include "metacommand.hh"
#include <deque>
#include <iostream>
#include <optional>
#include <string>

class ParsingException : public std::exception {
public:
  ParsingException(std::string const &error_description)
      : error_(error_description) {}
  const char *what() const noexcept override { return error_.c_str(); }

private:
  std::string error_;
};

class RegressionTestsParser {
public:
  RegressionTestsParser(std::string const &directory_location);
  int parseFile(std::string const &file_location);

private:
  static std::optional<Metacommand> determineMetacommand(std::string const &s);
  void executeCommand(std::deque<std::string> const &words);
  void executeThen(std::string const &expected_line);
  void executeThenNo(std::string const &not_expected_line);
  ParsingException generateError(std::string const &line,
                                 std::string const &error_ending);
  bool lineFound(std::string const &expected_line) const;
  bool isCommentLine(std::string const &line_word) const;
};
