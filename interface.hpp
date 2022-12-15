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
  Factory<std::string, Converter, std::string, std::string, unsigned long,
          unsigned long>
      factory;

 public:
  Interface(std::vector<std::string> inputs);
  ~Interface();
  void do_conv();
  void set_data(std::vector<std::pair<std::string, std::vector<unsigned long>>> data);
  //void call_muter(unsigned long number);
  //void call_mixer(unsigned long number);
};

#endif