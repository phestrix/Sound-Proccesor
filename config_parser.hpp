#ifndef CONFIG_PARSER
#define CONFIG_PARSER
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>

class CFG{
  private:
  std::vector<std::pair<std::string, std::vector<unsigned long>>> data;
  unsigned long parse_str(const std::string &s); 
  public:
  CFG();
  ~CFG();
  int parse_args(std::string filename);
};
#endif