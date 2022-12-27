#include "cfg_parser.hpp"

#include <sstream>

#include "../errors/io_errors.hpp"

/// @brief for case if "#     "
/// @param str string to check
/// @return
static bool IsComment(std::string& str) {
  while (!str.empty() && str[0] == ' ') {
    str.erase(0, 1);
  }
  return str.empty() || str[0] == '#';
}

/// @brief for case "#....."
/// @param str string to check
static void RemoveCommentAtEnd(std::string& str) {
  str = str.substr(0, str.find('#'));
}

ConfigParser::ConfigParser(std::string file_path) : m_file_path(file_path) {
  m_fin.open(m_file_path, std::ios_base::in);
  if (!m_fin.good()) {
    throw FileNotOpen(m_file_path);
  }
}

ConverterCommand ConfigParser::GetConverterComand() {
  ConverterCommand cvt_cmd;
  std::string buf;

  do {
    if (m_fin.eof()) {
      return cvt_cmd;
    }
    getline(m_fin, buf);
  } while (IsComment(buf));

  RemoveCommentAtEnd(buf);

  std::istringstream ssin(buf);
  ssin >> buf;
  cvt_cmd.push_back(buf);

  while (ssin >> buf) {
    cvt_cmd.push_back(buf);
  }

  return cvt_cmd;
}