#ifndef CONFIG_PARSER
#define CONFIG_PARSER
#include <fstream>
#include <vector>

class Parser_cfg {
 private:
  std::ifstream config_file;
  std::vector<unsigned> mute_seconds;
  std::vector<std::pair<std::string, unsigned>> stream_seconds_for_mix;
  std::string buffer;

 public:
  Parser_cfg(std::string filename) { config_file.open(filename); };
  ~Parser_cfg() {
    if (config_file.is_open()) {
      config_file.close();
    }
  };

  
  std::vector<unsigned>* read_seconds(std::string* str,
                                      std::vector<unsigned>* res);
  std::vector<unsigned>* read_stream_and_second(std::string* str,
                                                std::vector<unsigned>* res);
  void parse_config_file();
  char* get_conv();
};

#endif