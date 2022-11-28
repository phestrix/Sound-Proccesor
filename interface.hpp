#ifndef INTERFACE
#define INTERFACE
#include "converter.hpp"
#include "parser.hpp"


class Interface {
 private:
  std::string input_file;
  std::string ouput_file;

 public:
  Interface(std::string filename_input, std::string filename_output)
      : input_file(filename_input), ouput_file(filename_output) {
    Factory<std::string, Converter> Converter_Factory;
    Converter_Factory.add<Muter>("muter");
    Converter_Factory.add<Mixer>("mixer");
  };
  
  void mute(unsigned start_sec, unsigned end_sec);
  void mix();
};

#endif