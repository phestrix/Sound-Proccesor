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

Muter::Muter(std::string filename_in, std::string filename_out, unsigned s_sec,
             unsigned e_sec)
    : input_file(filename_in),
      ouput_file(filename_out),
      start(s_sec),
      end(e_sec) {}

void Muter::convert() {
  Parser parser(input_file, ouput_file);
  start*=parser.get_bytes_per_second();
  end*=parser.get_bytes_per_second();
  parser.mute_samples(&start, &end);
}