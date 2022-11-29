#include "interface.hpp"

#include <algorithm>
#include <utility>

Interface::Interface(std::string output, std::string cfg_file,
                     std::vector<std::string> inputs) {
  Parser_cfg cfg(cfg_file);
  cfg.parse_config_file();
  mode = cfg.get_conv();
  seconds = cfg.get_seconds();
  stream_to_mix = cfg.get_streams_and_seconds();
  
}

Interface::~Interface() {
 
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

void Interface::call_muter() {
  factory.add<Muter>("Muter");
  Converter* muter = factory.get("Muter")(this->input_files[0], this->output_file, this->seconds[0], this->seconds[1]);
  muter->convert();
  
}