#include "config_parser.hpp"

#include <algorithm>
#include <cstring>

void Parser_cfg::parse_config_file() {
  std::string buf;
  char a = '#';
  while (config_file.good()) {
    std::getline(config_file, buf);
    if (buf.at(0) == a) {
      buf.clear();
      std::getline(config_file, buf);
    }

    std::string mix = "mix";
    std::string mute = "mute";

    // find number of stream and number, than push them to vector of pair
    if (buf.find(mix)) {
      std::vector<unsigned> res;
      read_stream_and_second(&buf, &res);
      std::string tmp = "input" + res.at(0);
      stream_seconds_for_mix.push_back(std::make_pair(tmp, res.at(1)));
      tmp.~basic_string();
      res.clear();
      buffer.push_back('x');
    }

    // find seconds to mute and push them in vector of seconds
    if (buf.find(mute)) {
      std::vector<unsigned> res;
      read_seconds(&buf, &res);
      mute_seconds.push_back(res.at(0));
      mute_seconds.push_back(res.at(1));
      res.clear();
      buffer.push_back('x');
    }
  }
};

std::vector<unsigned>* Parser_cfg::read_seconds(std::string* str,
                                                std::vector<unsigned>* res) {
  if (str->find(" ")) {
    size_t pos = str->find(" ");
    if (str->find(" ", pos + 1)) {
      size_t interval = str->find(" ", pos + 1);
      unsigned number = 0;
      unsigned pow = 1;
      while (pos < interval) {
        number += ((pow) * (unsigned)str->at(pos));
        pow *= 10;
        ++pos;
      }
      res->push_back(number);
      if (str->find(" ", interval + 1)) {
        pos = str->find(" ", interval + 1);
        pow = 1;
        number = 0;
        while (pos < str->length()) {
          number += (pow) * (unsigned)str->at(pos);
          pow *= 10;
          ++pos;
        }
        res->push_back(number);
        return res;
      } else {
        res->push_back(UINT32_MAX);
        return res;
      }
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}

std::vector<unsigned>* read_stream_and_second(std::string* str,
                                              std::vector<unsigned>* res) {
  if (!str || !res) {
    return NULL;  // null pointer in function
  }
  if (str->find("$")) {
    unsigned number = 0;
    unsigned pow = 1;
    size_t pos = str->find("$") + 1;
    size_t interval = str->find(" ", pos - 1);

    if (pos == interval) {
      return NULL;  // case if "mix $ ..., need mix $(number) ..."
    }

    if (str->find(" ", interval) == str->length()) {
      return NULL;  // case if no seconds after number of stream
    }

    pos = str->length();
    while (pos > interval) {
      number += (pow * (unsigned)str->at(pos));
      pow *= 10;
      --pos;
    }

    res->push_back(number);
    return res;

  } else {
    return NULL;
  }
}

char* Parser_cfg::get_conv() {
  char a = buffer.at(0);
  std::reverse(buffer.begin(), buffer.end());
  buffer.pop_back();
  std::reverse(buffer.begin(), buffer.end());
  return &a;
}