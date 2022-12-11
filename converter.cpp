#include "converter.hpp"

#include <iostream>

#include "parser.hpp"

/*Converter::Converter(std::string filename) { current_stream = filename; }

void Converter::mute_sample(unsigned start, unsigned end) {
  if (start > end) {
    throw std::invalid_argument("start second should be less than end second");
    return;
  }

  Parser cur_stream(current_stream);
  unsigned byte_shift = start * cur_stream.get_bytes_per_second();
  unsigned bytes_to_mute = end - start * (cur_stream.get_bytes_per_second());
  cur_stream.mute_samples(&byte_shift, &bytes_to_mute);
}*/

Muter::Muter(std::string filename_in, std::string filename_out,
             unsigned long s_sec, unsigned long e_sec)
    : input_file(filename_in),
      ouput_file(filename_out),
      start(s_sec),
      end(e_sec) {}

void Muter::convert() {
  Parser parser(input_file, ouput_file);
  start = parser.get_bytes_per_second();
  end = parser.get_bytes_per_second();
  parser.mute_samples(&start, &end);
}

Muter::~Muter() {}

Mixer::Mixer(std::string filename_in, std::string filename_out,
             unsigned long s_sec, unsigned long e_sec)
    : in(filename_in), out(filename_out), s_second(s_sec) {}

Mixer::Mixer(std::string filename_in, std::string filename_out)
    : in(filename_in), out(filename_out), s_second(0) {}

Mixer::~Mixer() {}

void Mixer::convert() {
  Parser parser(in, out);
  unsigned long bytes = 1 * parser.get_bytes_per_second();
  unsigned long tmp = (unsigned long)parser.get_eof_byte();
  for (unsigned long i = s_second; i < tmp; ++i) {
    parser.copy_samples(&i, &bytes);
  }
}

Converter::~Converter() {}
