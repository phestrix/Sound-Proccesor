#ifndef CFG_PARSER
#define CFG_PARSER
#include <fstream>
#include <string>
#include <vector>

using ConverterCommand = std::vector<std::string>;

class ConfigParser {
 private:
  std::string m_file_path;
  std::ifstream m_fin;

 public:
  explicit ConfigParser(std::string file_path);
  ConverterCommand GetConverterComand();
};

#endif