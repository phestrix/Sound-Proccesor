#include "config_parser.hpp"

static unsigned long parse_int(std::string s) {
  unsigned long elem = 0;
  if (s[0] == '$') {
    s = s.substr(1, s.length());
  }

  unsigned long ten_deg = 1;
  for (size_t h = 0; h < s.length(); h++) {
    if (!(s[s.length() - 1 - h] - 48 >= 0 && s[s.length() - 1 - h] - 48 <= 9)) {
      throw std::invalid_argument(
          "Exception: Wrong parameters format (must be integer)");
    }

    elem += ten_deg * (unsigned long)(s[s.length() - 1 - h] - 48);
    ten_deg *= 10;
  }
  return elem;
}

unsigned long CFG::parse_str(const std::string &s) {
  if (s.length() < 6) {
    throw std::invalid_argument("Exception: Wrong length of config's string");
  }

  if (s.substr(0, 5) == "mute ") {
    std::string s1 = s.substr(5, s.length());
    std::size_t k = s1.find(' ');

    if (k == std::string::npos) {
      throw std::invalid_argument(
          "Exception: Wrong config's string (count of mute parameters must be "
          "2)");
    }

    std::string s2 = s1.substr(0, k), s3 = s1.substr(k + 1, s1.length());
    unsigned long res1 = parse_int(s2), res2 = parse_int(s3);
    std::pair<std::string, std::vector<unsigned long>> el;
    el.first = "mute";
    std::vector<unsigned long> params;
    params.push_back(res1);
    params.push_back(res2);
    el.second = params;
    data.push_back(el);

  } else if (s.substr(0, 4) == "mix ") {
    std::string s1 = s.substr(4, s.length());
    std::size_t k = s1.find(' ');

    if (k == std::string::npos) {
      throw std::invalid_argument(
          "Exception: Wrong config's string (count of mix parameters must be "
          "2)");
    }

    std::string s2 = s1.substr(0, k), s3 = s1.substr(k + 1, s1.length());
    unsigned long res1 = parse_int(s2), res2 = parse_int(s3);
    std::pair<std::string, std::vector<unsigned long>> el;
    el.first = "mix";
    std::vector<unsigned long> params;
    params.push_back(res1);
    params.push_back(res2);
    el.second = params;
    data.push_back(el);
  }

  else
    throw std::invalid_argument(
        "Exception: Wrong config's string (must be mute or mix)");

  return 0;
}

CFG::CFG() {}
CFG::~CFG() {}

int CFG::parse_args(std::string filename) {
  std::ifstream fin;
  fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  std::string cur_s;

  try {
    std::string f = filename;
    fin.open(f);
  } catch (std::ifstream::failure &e) {
    throw std::invalid_argument("Exception: Wrong path to configs");
  }

  bool end = false;
  while (!end) {
    try {
      getline(fin, cur_s);
      if (cur_s.length() >= 1 && cur_s[0] != '#') {
        parse_str(cur_s);
      }

    } catch (std::ifstream::failure &e) {
      end = true;
    }
  }
  fin.close();
  return 0;
}


