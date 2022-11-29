#include "interface.hpp"

Interface::Interface(std::string output, std::string cfg_file,
                     std::vector<std::string> inputs) {
  Parser_cfg cfg(cfg_file);
  cfg.parse_config_file();
  mode = cfg.get_conv();
  seconds = cfg.get_seconds();
  stream_to_mix = cfg.get_streams_and_seconds();
  cfg.~Parser_cfg();
  output_file.open(output);
  for (size_t i = 0; i < inputs.size(); ++i) {
    input_files[i].open(inputs[i]);
  }
}