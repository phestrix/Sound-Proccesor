#ifndef INTERFACE
#define INTERFACE
#include <fstream>
#include <vector>

#include "config_parser.hpp"
#include "converter.hpp"

class Interface {
 private:
  std::string input_files;
  std::string output_file;
  std::string mode;
  std::vector<unsigned> seconds;
  std::vector<std::pair<std::string, unsigned>> stream_to_mix;
  Factory<std::string, Converter, std::string, std::string, unsigned, unsigned> factory;

 public:
  Interface(std::string output, std::string cfg_file,
            std::string inputs);
  ~Interface();
  void do_conv();
  void call_muter();
  void call_mixer();
};

#endif