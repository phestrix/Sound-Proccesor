#include "command_line_parser.hpp"

#include <vector>

#include "interface.hpp"

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
  Interface interface(names.at(4), names.at(3), names.at(5));
}