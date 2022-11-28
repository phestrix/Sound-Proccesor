#include "config_parser.hpp"

#include <cstring>

static unsigned find_numbers(size_t* i1, size_t* i2, std::string* str,
                             size_t* pos1, size_t* pos2) {
  *i1 = str->find(" ", *pos1);
  *i2 = str->find(" ", *pos2);
  unsigned return_sec = 0;
  unsigned pow = 1;
  for (i2; i2 > i1; --i2) {
    return_sec += (pow * (unsigned)str->at(*i2));
    pow *= 10;
  }
  return return_sec;
}

std::vector<unsigned>* Parser_cfg::read_stream_and_second() {
  buf = new char[20];
  config_file.getline(buf, 20, '\n');
  std::string tmp = buf;
  size_t pos_of_stream = tmp.find("$");
  std::vector<unsigned> res;
  res.push_back((unsigned)tmp.at(pos_of_stream + 1));  // add number of stream
  size_t pos_after_stream =
      tmp.find(" ", pos_of_stream + 1);  // find next " " before number
  size_t i1 = tmp.find(" ", pos_after_stream + 1);  // find " " after number
  size_t diff = i1 - pos_after_stream;              // difference between them
  unsigned second = 0;
  for (size_t i = 0; i < diff; ++i) {
    second += ((10 * i + 1) * tmp.at(i1 - i));  // add number to numeral
  }
  res.push_back(second);
  delete[] buf;
  return &res;
}

std::vector<unsigned>* Parser_cfg::read_seconds() {
  buf = new char[20];
  config_file.getline(buf, 20, '\n');
  std::string tmp = buf;
  size_t i1 = 0;
  size_t i2 = i1 + 1;
  unsigned start_sec = find_numbers(&i1, &i2, &tmp, &i1, &i2);
  unsigned end_sec = find_numbers(&i1, &i2, &tmp, &i2, &i1);
  delete[] buf;
  std::vector<unsigned> res;
  res.push_back(start_sec);
  res.push_back(end_sec);
  return &res;
}

char* Parser_cfg::read_conv() {
  buf = new char[4];
  config_file.read(buf, 4);
  if (strcmp(buf, "mix")) {
    delete[] buf;
    return "mix";
  }
  if (strcmp(buf, "mute")) {
    delete[] buf;
  
    return "mute";
  }
  delete[] buf;
  return NULL;
}