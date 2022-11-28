#include "config_parser.hpp"

#include <cstring>

void Parser_cfg::parse_config_file() {
  std::string buf;
  char a[2] = "#";

  std::getline(config_file, buf);
  if (buf.at(0) == *a) {
    buf.clear();
    std::getline(config_file, buf);
  }
  std::string mix = "mix";
  std::string mute = "mute";
  if (buf.find(mix)) {
    read_stream_and_second(&buf);
  }
  if (buf.find(mute)) {
    read_seconds(&buf);
  }
};

std::vector<unsigned>* Parser_cfg::read_seconds(std::string* str) {
  if (str->find(" ")) {
    size_t pos = str->find(" ");
    if (str->find(" ", pos + 1)) {
      size_t interval = str->find(" ", pos + 1);
      std::vector<unsigned> res;
      unsigned number = 0;
      unsigned pow = 1;
      while (interval > pos) {
        number += ((pow) * (unsigned)str->at(interval));
        pow *= 10;
        --interval;
      }
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}

std::vector<unsigned>* read_stream_and_second(std::string* str) {
  if (!str->find("$")) {
    return NULL;
  }
}