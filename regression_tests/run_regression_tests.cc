#include "regression_tests_parser.hh"
#include <filesystem>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Al least one argument needs to be passed!\n";
    return -1;
  }
  const std::string TESTING_DIRECTORY_ROOT = (argc == 2) ? argv[1] : argv[2];
  if (argc == 2) {
    std::filesystem::remove_all(TESTING_DIRECTORY_ROOT);
  }
  std::filesystem::create_directory(TESTING_DIRECTORY_ROOT);
  std::string test_location(TESTFILES_LOCATION + std::string(argv[1]));

  RegressionTestsParser parser(TESTING_DIRECTORY_ROOT);
  auto result = parser.parseFile(test_location);
  return result;
}
