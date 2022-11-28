#ifndef CONFIG_PARSER
#define CONFIG_PARSER
#include <fstream>
#include <vector>

class Parser_cfg {
 private:
  std::ifstream config_file;

 public:
  Parser_cfg(std::string filename) { config_file.open(filename); };
  ~Parser_cfg() {
    if (config_file.is_open()) {
      config_file.close();
    }
  };

  char* read_conv();
  std::vector<unsigned>* read_seconds(std::string* str);
  std::vector<unsigned>* read_stream_and_second(std::string* str);
  void parse_config_file();
};

#endif