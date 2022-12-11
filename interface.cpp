#include "interface.hpp"

#include <algorithm>

#include "config_parser.hpp"

Interface::Interface(std::vector<std::string> inputs) {
  for (auto it = inputs.begin(); it < inputs.end(); ++it) {
    if (it->find("config")) {
      cfg_file = *it;
    } else {
      if (it->find("input") && it->find(".wav")) {
        input_files.push_back(*it);
      } else {
        if (it->find("output") && it->find(".wav")) {
          output_file = *it;
        }
      }
    }
  }
  Parser_cfg cfg(cfg_file);
  if (!cfg.parse_config_file()) {
    throw std::invalid_argument("Something wrong in cfg file");
  }
  mode = *cfg.get_conv();
  seconds = *cfg.get_seconds();
  stream_to_mix = *cfg.get_streams_and_seconds();
}

Interface::~Interface() {}

static void rstr_pop(std::string* str) {
  std::reverse(str->begin(), str->end());
  str->pop_back();
  std::reverse(str->begin(), str->end());
}

void Interface::do_conv() {
  for (unsigned long i = 0; i < input_files.size(); ++i) {
    char tmp = mode.at(0);
    rstr_pop(&mode);
    if (tmp == 'x') {
      call_mixer(i);
    } else {
      if (tmp == 'm') {
        call_muter(i);
      }
    }
  }
}

void Interface::call_mixer(unsigned long number) {
  factory.add<Mixer>("Mixer");
  Converter* mixer = factory.get("Mixer")(
      this->stream_to_mix[number].first, this->output_file,
      this->stream_to_mix[number].second, this->seconds[1]);
  mixer->convert();
}

void Interface::call_muter(unsigned long number) {
  factory.add<Muter>("Muter");
  Converter* muter =
      factory.get("Muter")(this->input_files[number], this->output_file,
                           this->seconds[0], this->seconds[1]);
  muter->convert();
}