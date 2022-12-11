#include "command_line_parser.hpp"

#include <vector>

#include "config_parser.hpp"
#include "interface.hpp"

static bool check_args(std::vector<std::string>* arr) {
  for (size_t i = 0; i < arr->size(); ++i) {
    if ((arr->at(0).find("out") || arr->at(i).find("in")) &&
        (arr->at(0).find("conf") || arr->at(i).find("cfg")))
      return false;
    if (arr->at(i).find("out") && arr->at(i).find("in")) return false;
  }
  if (!arr->at(2).find(".txt")) return false;
  if (!arr->at(3).find(".wav")) return false;
  if (!arr->at(4).find(".wav")) return false;
  return true;
}

Parser_cmd::Parser_cmd(int* ac, char* av[]) {
  std::vector<std::string> names;
  bool need_help = false;
  bool run = false;
  for (int i = 0; i < *ac; ++i) {
    std::string cur_arg = av[i];
    if (cur_arg[0] != '-')
      names.push_back(cur_arg);
    else if (cur_arg.length() != 2)
      throw std::invalid_argument("Wrong parameter");
    else if (cur_arg[1] == 'h')
      need_help = true;
    else if (cur_arg[1] != 'c')
      throw std::invalid_argument("Wrong parameter");
    else if (cur_arg[0] == '-' && cur_arg[1] == 'c')
      run = true;
  }
  if (need_help) {
  };
  if (!run) throw std::invalid_argument("Wrong parameters");
  if (names.size() < 3) {
    throw std::invalid_argument(
        "Too few arguments\nMust be 4 or more, for mode, inputs, output");
  }
  if (!check_args(&names)) throw std::invalid_argument("Wrong arguments");
  Interface interface(names);
  interface.do_conv();
}

Parser_cmd::~Parser_cmd() {}
