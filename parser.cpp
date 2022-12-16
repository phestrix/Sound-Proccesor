#include "parser.hpp"

#include <cstring>
#include <iostream>
#define CONST_HEAD_SIZE 44

// loop that fill char* fields in WAVheader from buffer
// than increase precision
static void loop(size_t* prec, char* s1, char* s2, size_t end_of_loop) {
  if (!s1 || !s2) {
    throw std::invalid_argument("Empty buffers in loop");
  }
  for (size_t i = 0; i < end_of_loop; ++i) {
    s1[i] = s2[i + *prec];
  }
  *prec += end_of_loop;
  if (*prec >= 44) {
    throw std::invalid_argument("Something wrong in precision in parser");
  }
}

// cast to typename of field( from WAVheader) from buffer
// than increase precision
template <typename T>
void cast_to(T val, char* s, size_t* prec) {
  if (!s) {
    throw std::invalid_argument("empty buffer in cast");
  }
  val = (T) * (&s[*prec]);
  *prec += sizeof(T);
  // std::cout << typeid(val).name() << " " << sizeof(T) << " " <<
  // sizeof(unsigned int) << std::endl;

  if (*prec > 44) {
    throw std::invalid_argument("Something wrong in precision in parser");
  }
}

static WAVheader* parse(char* buf) {
  WAVheader* res = (WAVheader*)malloc(CONST_HEAD_SIZE);
  size_t precision = 0;
  loop(&precision, res->chunk_id, buf, 4);                         // 4
  cast_to<unsigned int>(res->chunk_size, buf, &precision);         // 8
  loop(&precision, res->format, buf, 4);                           // 12
  loop(&precision, res->subchunk1_id, buf, 4);                     // 16
  cast_to<unsigned int>(res->subchunk1_size, buf, &precision);     // 20
  cast_to<unsigned short>(res->audio_format, buf, &precision);     // 22
  cast_to<unsigned short>(res->num_channels, buf, &precision);     // 24
  cast_to<unsigned int>(res->sample_rate, buf, &precision);        // 28
  cast_to<unsigned int>(res->byte_rate, buf, &precision);          // 32
  cast_to<unsigned short>(res->block_align, buf, &precision);      // 34
  cast_to<unsigned short>(res->bits_per_sample, buf, &precision);  // 36
  loop(&precision, res->subchunk2_id, buf, 4);                     // 40
  cast_to<unsigned int>(res->subchunk2_size, buf, &precision);     // 44
  return res;
};

// defalut constructor
Parser::Parser(std::string filename_in, std::string filename_out) {
  char* tmp = new char[CONST_HEAD_SIZE];
  input_file.open(filename_in);
  input_file.read(tmp, CONST_HEAD_SIZE);
  std::ofstream log("log.txt");
  log.write(tmp, CONST_HEAD_SIZE);
  header = parse(tmp);
  delete[] tmp;
  if (!check_input()) {
    throw std::invalid_argument("not able to find \"data\" chunk");
  }

  output_file.open(filename_out);
}

// constructor if no out file
Parser::Parser(std::string filename_in) {
  char* tmp = new char[CONST_HEAD_SIZE];
  input_file.open(filename_in);
  input_file.read(tmp, CONST_HEAD_SIZE);

  header = parse(tmp);
  delete[] tmp;
  if (!check_input()) {
    throw std::invalid_argument("not able to find \"data\" chunk");
  }

  output_file.open(filename_in + "out");
  output_file.write(tmp, CONST_HEAD_SIZE);
}

// destructor
Parser::~Parser() {
  if (input_file.is_open()) {
    input_file.close();
  }
  if (output_file.is_open()) {
    output_file.close();
  }
  if (header) {
    free(header);
  }
}

bool Parser::check_input() {
  
  if (!strcmp(header->chunk_id, "RIFF")) {
    return false;
  }
  std::cout << header->chunk_id << std::endl;
  if (!strcmp(header->format, "WAVE")) {
    return false;
  }
  if (!strcmp(header->subchunk1_id, "fmt ")) {
    return false;
  }
  if (header->subchunk1_size != 16) {
    std::cout << header->subchunk1_size << std::endl;
    return false;
  }
  if (header->audio_format != 1) {
    std::cout << "5" << std::endl;
    return false;
  }
  if (header->num_channels != 1) {
    std::cout << "6" << std::endl;
    return false;
  }
  if (header->sample_rate != 44100) {
    return false;
  }
  if (header->bits_per_sample != 16) {
    return false;
  }
  if (!strcmp(header->subchunk2_id, "data")) {
    while (input_file.good()) {
      find_data_in_header();
    }
    if (!strcmp(header->subchunk2_id, "data")) {
      return false;
    }
  }
  return true;
}

bool Parser::find_data_in_header() {
  char* buf = new char[4];
  input_file.read(buf, 4);
  if (!strcmp(buf, "data")) {
    input_file.seekg(1);
    return false;
  }
  byte_after_data = input_file.tellg();
  for (size_t i = 0; i < 4; ++i) {
    header->subchunk2_id[i] = buf[i];
  }
  input_file.seekg(4);
  input_file.read(buf, 4);
  header->subchunk2_size = (unsigned int)*(&buf[0]);
  delete[] buf;
  return true;
}

unsigned int Parser::get_bytes_per_second() { return header->byte_rate; }

bool Parser::check_args(unsigned int* shift, unsigned int* bytes_to_change) {
  size_t check = get_eof_byte();
  if ((*shift) > check) {
    return false;
  }
  if (*bytes_to_change > check) {
    return false;
  }
  if ((*shift + *bytes_to_change) > check) {
    *bytes_to_change = (check - *shift);
  }
  return true;
}

// mute
void Parser::mute_samples(unsigned int* shift, unsigned int* bytes_to_change) {
  if (!check_args(shift, bytes_to_change)) {
    throw std::invalid_argument("file doesnt contain this amount of seconds");
    return;
  }

  input_file.seekg(*shift + byte_after_data);
  output_file.seekp(*shift + byte_after_data);
  char* tmp_block = new char[*bytes_to_change];
  for (size_t i = 0; i < *bytes_to_change; ++i) {
    tmp_block[i] ^= tmp_block[i];
  }
  output_file.write(tmp_block, *bytes_to_change);
  delete[] tmp_block;
}

// copy
void Parser::copy_samples(unsigned int* shift, unsigned int* bytes_to_change) {
  if (!check_args(shift, bytes_to_change)) {
    throw std::invalid_argument("file doesnt contain this amount of seconds");
    return;
  }

  input_file.seekg(*shift + byte_after_data);
  char* tmp = new char[*bytes_to_change];
  input_file.read(tmp, *bytes_to_change);
  output_file.seekp(*shift + byte_after_data);
  output_file.write(tmp, *shift);
  delete[] tmp;
}

size_t Parser::get_eof_byte() {
  size_t tmp = input_file.tellg();
  input_file.seekg(0, std::ios::end);
  size_t check = input_file.tellg();
  input_file.seekg(tmp);
  return check;
}
