#ifndef CL_PARSER
#define CL_PARSER
#include <string>
#include <vector>

#define CONVERTERS_CONFIG_FILE "converters_description.json"

struct Options{
  std::string m_output_file;
  std::string m_config_file;
  std::vector<std::string> m_input_files;
  Options() = default;
};

bool GetOptions(int argc, char** argv, Options& opts);

#endif