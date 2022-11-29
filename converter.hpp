#ifndef CONVERTER
#define CONVERTER
#include <string>

#include "template_factory.hpp"

class Converter {
 public:
  Converter(){};
  virtual void convert() = 0;
  virtual ~Converter();
};

class Muter : public Converter {
 private:
  std::string input_file;
  std::string ouput_file;
  unsigned start;
  unsigned end;
  

 public:
 Muter(std::string filename_in, std::string filename_out, unsigned s_sec, unsigned e_sec);
  void convert();
  ~Muter();
};

class Mixer : public Converter {
 private:
  std::string input_file;
  std::string ouput_file;
  unsigned end;
  std::string to_mix;

 public:
  void convert();
  ~Mixer();
};

#endif