#ifndef COMMAND_LINE_PARSER
#define COMMAND_LINE_PARSER
#include <fstream>
#include <vector>

class Parser_cmd {
 private:
  public:
  Parser_cmd(int* ac, char* av[]);
  ~Parser_cmd();
};

#endif