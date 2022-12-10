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
  unsigned long start;
  unsigned long end;
  

 public:
 Muter(std::string filename_in, std::string filename_out, unsigned long s_sec, unsigned long e_sec);
  void convert();
  ~Muter();
};

class Mixer : public Converter {
 private:
  unsigned long second;
  std::string in;
  std::string out;

 public:
  void convert();
  Mixer(std::string filename_in, std::string filename_out, unsigned long sec);
  Mixer(std::string filename_in, std::string filename_out);
  ~Mixer();
};

#endif