#ifndef INTERFACE
#define INTERFACE
#include <fstream>
#include <vector>

#include "converter.hpp"

class Interface {
 private:
  std::vector<std::string> input_files;
  std::string output_file;
  std::vector<std::pair<std::string, std::vector<unsigned long>>> data;
 // std::vector<unsigned long> seconds;//for mute
 // std::vector<std::pair<std::string, std::pair<unsigned long, unsigned long>>> stream_to_mix;//for mix
  Factory<std::string, Converter, std::string, std::string, unsigned long,
          unsigned long>
      factory;

 public:
  Interface(std::vector<std::string> inputs);
  ~Interface();
  void do_conv();
  void call_muter(unsigned long number);
  void call_mixer(unsigned long number);
};

#endif