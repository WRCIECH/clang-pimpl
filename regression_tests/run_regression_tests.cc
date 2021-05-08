#include "regression_tests_parser.hh"
#include <filesystem>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Al least two arguments needs to be passed!\n";
    return -1;
  }
  const std::string TESTING_DIRECTORY_ROOT = argv[1];
  const std::string TESTFILE_LOCATION = argv[2];

  std::filesystem::remove_all(TESTING_DIRECTORY_ROOT);
  std::filesystem::create_directory(TESTING_DIRECTORY_ROOT);

  RegressionTestsParser parser(TESTING_DIRECTORY_ROOT);
  return parser.parseFile(TESTFILE_LOCATION);
}
