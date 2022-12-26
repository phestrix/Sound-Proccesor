#include "converter.hpp"

#include <iostream>

#include "parser.hpp"
/// @brief 
/// @param filename_in file for input
/// @param filename_out file for output
/// @param s_sec second when start mute
/// @param e_sec second when mute ends
Muter::Muter(FILE* filename_in, FILE* filename_out, int s_sec, int e_sec)
    : input_file(filename_in), ouput_file(filename_out), start(s_sec), end(e_sec) {}
/**
 * 
 * 
 * 
*/
/// @brief func that calls wav parser to mute in input some seconds
void Muter::convert() {
  Parser parser(input_file, ouput_file);
  parser.mute(start, end);
}

Muter::~Muter() {}
/// @brief 
/// @param filename_in file for input
/// @param filename_out file for output
/// @param s_sec second when start mix
/// @param e_sec second when mix ends
Mixer::Mixer(FILE* filename_in, FILE* filename_out, int s_sec, int e_sec)
    : in(filename_in), out(filename_out), start(s_sec), end(e_sec) {}

Mixer::Mixer(FILE* filename_in, FILE* filename_out, int e_sec)
    : in(filename_in), out(filename_out), start(0), end(e_sec) {}

Mixer::~Mixer() {}

/// @brief func that calls wav parser to mix input file with output
void Mixer::convert() {
  Parser parser(in, out);
  parser.mix(start, end);
}

Converter::~Converter() {}
