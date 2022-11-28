#include "converter.hpp"
#include <iostream>

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

void Muter::convert() {
  if (start > end) {
    throw std::invalid_argument("start second should be less than end second");
    return;
  }
  
}