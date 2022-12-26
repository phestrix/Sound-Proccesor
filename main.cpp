#include "command_line_parser.hpp"
#include "parser.hpp"

int main(int ac, char* av[]) {
  Parser_cmd test(&ac, av);

  return 0;
}