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
  unsigned int start;
  unsigned int end;

 public:
  Muter(std::string filename_in, std::string filename_out, unsigned int s_sec,
        unsigned int e_sec);
  void convert();
  ~Muter();
};

class Mixer : public Converter {
 private:
  unsigned int s_second;
  unsigned int e_second;
  std::string in;
  std::string out;

 public:
  void convert();
  Mixer(std::string filename_in, std::string filename_out, unsigned int s_sec,
        unsigned int e_sec);
  Mixer(std::string filename_in, std::string filename_out, unsigned int e_sec);
  ~Mixer();
};

#endif