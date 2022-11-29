#include "interface.hpp"

#include <algorithm>

Interface::Interface(std::string output, std::string cfg_file,
                     std::vector<std::string> inputs) {
  Parser_cfg cfg(cfg_file);
  cfg.parse_config_file();
  mode = cfg.get_conv();
  seconds = cfg.get_seconds();
  stream_to_mix = cfg.get_streams_and_seconds();
  output_file.open(output);
  for (size_t i = 0; i < inputs.size(); ++i) {
    input_files[i].open(inputs[i]);
  }
}

static void rstr_pop(std::string* str) {
  std::reverse(str->begin(), str->end());
  str->pop_back();
  std::reverse(str->begin(), str->end());
}

void Interface::do_conv() {
  char tmp = mode.at(0);
  rstr_pop(&mode);
  if (tmp == 'x') {
    call_mixer();
  } else {
    if (tmp == 'm') {
      call_muter();
    }
  }
}

void Interface::call_mixer() {}

void Interface::call_muter() {}