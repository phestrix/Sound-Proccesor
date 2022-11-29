#ifndef INTERFACE
#define INTERFACE
#include <fstream>
#include <vector>

#include "config_parser.hpp"

class Interface {
 private:
  std::vector<std::ifstream> input_files;
  std::ofstream output_file;
  char mode;
  std::vector<unsigned> seconds;
  std::vector<std::pair<std::string, unsigned>> stream_to_mix;

 public:
  Interface(std::string output, std::string cfg_file,
            std::vector<std::string> inputs);
  ~Interface();
};

#endif