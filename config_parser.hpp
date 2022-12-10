#ifndef CONFIG_PARSER
#define CONFIG_PARSER
#include <fstream>
#include <vector>

class Parser_cfg {
 private:
  std::ifstream config_file;
  std::vector<unsigned long> mute_seconds;
  std::vector<std::pair<std::string, unsigned long>> stream_seconds_for_mix;
  std::string buffer;

 public:
  Parser_cfg(std::string filename) { config_file.open(filename); };
  ~Parser_cfg() {
    if (config_file.is_open()) {
      config_file.close();
    }
  };

  std::vector<unsigned long>* read_seconds(std::string* str,
                                           std::vector<unsigned long>* res);
  std::vector<unsigned long>* read_stream_and_second(
      std::string* str, std::vector<unsigned long>* res);
  bool parse_config_file();
  std::string* get_conv();
  std::vector<unsigned long>* get_seconds();
  std::vector<std::pair<std::string, unsigned long>>* get_streams_and_seconds();
};

#endif