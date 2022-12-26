#ifndef INTERFACE
#define INTERFACE
#include <algorithm>
#include <fstream>
#include <vector>

#include "config_parser.hpp"
#include "converter.hpp"
#include "interface.hpp"

class Interface {
 private:
  std::vector<std::string> input_files;
  std::string output_file;
  std::vector<FILE*> in_files;
  FILE* output;
  std::vector<std::pair<std::string, std::vector<int>>> data;
  Factory<std::string, Converter, FILE*, FILE*, int, int> factory;
  bool open_files();

 public:
  Interface(std::vector<std::string> inputs);
  ~Interface();
  void do_conv();
  void set_data(std::vector<std::pair<std::string, std::vector<int>>> data);
};

#endif