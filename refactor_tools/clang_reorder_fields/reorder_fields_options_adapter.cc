#include "refactor_tools/clang_reorder_fields/reorder_fields_options_adapter.hh"
#include <boost/algorithm/string.hpp>
#include <boost/throw_exception.hpp>
#include <iostream>

// Boost complains for some unknown reasons...
#define BOOST_NO_EXCEPTIONS
void boost::throw_exception(std::exception const &e) {}

ReorderFieldsOptionsAdapterForCommandLine::
    ReorderFieldsOptionsAdapterForCommandLine()
    : record_name_{"record-name", llvm::cl::Required,
                   llvm::cl::desc("The name of the struct/class."),
                   llvm::cl::cat(clang_reorder_fields_category_)},
      fields_order_{"fields-order", llvm::cl::CommaSeparated,
                    llvm::cl::OneOrMore,
                    llvm::cl::desc("The desired fields order."),
                    llvm::cl::cat(clang_reorder_fields_category_)},
      clang_reorder_fields_category_{"clang-reorder-fields options"},
      usage_{"A tool to reorder fields in C/C++ structs/classes.\n"},
      inplace_{"i", llvm::cl::desc("Overwrite edited files.")} {}

// Map creation needs to happen here as in constructor the category fields is
// still not filled.
CommandMaps const &ReorderFieldsOptionsAdapterForCommandLine::getCommands() {
  command_maps_.string_map["record-name"] = record_name_;
  command_maps_.array_map["fields-order"] = fields_order_;
  return command_maps_;
}

ReorderFieldsOptionsAdapterForRegressionTests::
    ReorderFieldsOptionsAdapterForRegressionTests(std::string const &line)
    : line_(line) {
  std::vector<std::string_view> result;
  boost::split(result, line_, boost::is_any_of(" "));
  for (auto &c : result) {
    c.remove_prefix(std::min(c.find_first_not_of("-"), c.size()));
  }

  for (auto &c : result) {
    auto key = std::string(c.begin(), c.begin() + c.find_first_of("="));
    auto value = std::string(c.begin() + c.find_first_of("=") + 1, c.end());
    if (value.find(',') == std::string_view::npos) {
      values.push_back(std::move(value));
      command_maps_.string_map[key] = values.back();
    } else {
      std::vector<std::string> elems;
      boost::split(elems, value, boost::is_any_of(","));
      elements.push_back(std::move(elems));
      command_maps_.array_map[key] = elements.back();
    }
  }
}

CommandMaps const &
ReorderFieldsOptionsAdapterForRegressionTests::getCommands() {
  return command_maps_;
}