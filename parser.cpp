#include "parser.hpp"

#include <cstring>

Parser::Parser(std::string filename) {
  char tmp[44];
  input_file.open(filename, std::ifstream::binary);
  input_file.read(tmp, sizeof(WAVheader));
  header = (WAVheader*)tmp;
  if (!check_input()) {
    throw std::invalid_argument("not able to find \"data\" chunk");
  }
  std::string out_file = filename + "_out";
  output_file.open(out_file, std::ofstream::binary);
  output_file.write(tmp, 44);
}

Parser::~Parser() {
  if (input_file.is_open()) {
    input_file.close();
  }
  if (output_file.is_open()) {
    output_file.close();
  }
}

bool Parser::check_input() {
  if (!strcmp(header->chunk_id, "RIFF")) {
    return false;
  }
  if (!strcmp(header->format, "WAVE")) {
    return false;
  }
  if (!strcmp(header->subchunk1_id, "fmt ")) {
    return false;
  }
  if (header->subchunk1_size != 16) {
    return false;
  }
  if (header->audio_format != 1) {
    return false;
  }
  if (header->num_channels != 1) {
    return false;
  }
  if (header->sample_rate != 44100) {
    return false;
  }
  if (header->bits_per_sample != 16) {
    return false;
  }
  if (!strcmp(header->subchunk2_id, "data")) {
    if (!strcmp(header->subchunk2_id, "list")) {
      return false;
    } else {
      while (!input_file.eof()) {
        if (find_list_in_header()) {
          return true;
        }
      }
      return false;
    }
  }
  return true;
}

bool Parser::find_list_in_header() {
  char* buf = new char[4];
  input_file.read(buf, 4);
  if (!strcmp(buf, "list")) {
    input_file.seekg(4);
    return false;
  }
  for (char i = 0; i < 4; ++i) {
    header->subchunk2_id[i] = buf[i];
  }
  input_file.seekg(4);
  input_file.read(buf, 4);
  header->subchunk2_size = (unsigned long)&buf;
  delete[] buf;
  return true;
}

inline unsigned long Parser::get_bytes_per_second() {
  return header->byte_rate;
}

bool Parser::check_args(unsigned* shift, unsigned* bytes_to_change) {
  size_t tmp = input_file.gcount();
  if ((*shift) > tmp) {
    return false;
  }
  if (*bytes_to_change > tmp) {
    return false;
  }
  if ((*shift + *bytes_to_change) > tmp) {
    *bytes_to_change = (tmp - *shift);
  }
  return true;
}

// mute
void Parser::mute_samples(unsigned* shift, unsigned* bytes_to_change) {
  if (!check_args(shift, bytes_to_change)) {
    throw std::invalid_argument("file doesnt contain this amount of seconds");
    return;
  }

  input_file.seekg(*shift);
  output_file.seekp(*shift);
  char* tmp_block = new char[*bytes_to_change];
  for (size_t i = 0; i < *bytes_to_change; ++i) {
    tmp_block[i] ^= tmp_block[i];
  }
  output_file.write(tmp_block, *bytes_to_change);
  delete[] tmp_block;
}

// copy
void Parser::copy_samples(unsigned* shift, unsigned* bytes_to_change) {
  if (!check_args(shift, bytes_to_change)) {
    throw std::invalid_argument("file doesnt contain this amount of seconds");
    return;
  }

  input_file.seekg(*shift);
  char* tmp = new char[*bytes_to_change];
  input_file.read(tmp, *bytes_to_change);
  output_file.seekp(*shift);
  output_file.write(tmp, *shift);
}