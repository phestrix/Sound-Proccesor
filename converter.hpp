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
  FILE* input_file;
  FILE* ouput_file;
  int start;
  int end;

 public:
  Muter(FILE* filename_in, FILE* filename_out, int s_sec,
        int e_sec);
  void convert();
  ~Muter();
};

class Mixer : public Converter {
 private:
  int start;
  int end;
  FILE* in;
  FILE* out;

 public:
  void convert();
  Mixer(FILE* filename_in, FILE* filename_out, int s_sec, int e_sec);
  Mixer(FILE* filename_in, FILE* filename_out, int e_sec);
  ~Mixer();
};

#endif