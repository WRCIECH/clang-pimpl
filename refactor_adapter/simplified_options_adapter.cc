#include "simplified_options_adapter.hh"
#include <boost/algorithm/string.hpp>
#include <boost/throw_exception.hpp>
#include <iostream>

// Boost complains for some unknown reasons...
//#define BOOST_NO_EXCEPTIONS
//void boost::throw_exception(std::exception const &e) {}

SimplifiedOptionsAdapter::SimplifiedOptionsAdapter(std::string const &line)
    : line_(line) {
  std::vector<std::string> result;
  boost::split(result, line_, boost::is_any_of(" "));
  for (auto &c : result) {
    //c.remove_prefix(std::min(c.find_first_not_of("-"), c.size()));
      c.erase(0, std::min(c.find_first_not_of("-"), c.size()));
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

CommandMaps const &SimplifiedOptionsAdapter::getCommands() {
  return command_maps_;
}