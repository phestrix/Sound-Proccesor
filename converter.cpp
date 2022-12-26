#include "converter.hpp"

#include <iostream>

#include "parser.hpp"

Muter::Muter(FILE* filename_in, FILE* filename_out, int s_sec, int e_sec)
 : input_file(filename_in), ouput_file(filename_out), start(s_sec), end(e_sec) {}

void Muter::convert() {
  Parser parser(input_file, ouput_file);
  parser.mute(start, end);
}

Muter::~Muter() {}

Mixer::Mixer(FILE* filename_in, FILE* filename_out, int s_sec, int e_sec)
 : in(filename_in), out(filename_out), start(s_sec), end(e_sec) {}

Mixer::Mixer(FILE* filename_in, FILE* filename_out, int e_sec) : in(filename_in), out(filename_out), start(0), end(e_sec) {}

Mixer::~Mixer() {}

void Mixer::convert() {
  Parser parser(in, out);
  parser.mix(start, end);
}

Converter::~Converter() {}
