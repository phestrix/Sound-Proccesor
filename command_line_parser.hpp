#ifndef COMMAND_LINE_PARSER
#define COMMAND_LINE_PARSER

#include <fstream>

class Parser_cmd {
 private:
 void parse();

 public:
  Parser_cmd(int* ac, char* av[]);
  ~Parser_cmd();

};

#endif