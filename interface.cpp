#include "interface.hpp"

#include <algorithm>

#include "config_parser.hpp"

Interface::Interface(std::vector<std::string> inputs) {
  for (auto it = inputs.begin(); it < inputs.end(); ++it) {
    if (it->find("config")) {
      CFG parser;
      if (!parser.parse_args(inputs[0])) {
        throw std::invalid_argument("Something wrong in cfg file");
      }
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
}

Interface::~Interface() {}

static void rstr_pop(std::string* str) {
  std::reverse(str->begin(), str->end());
  str->pop_back();
  std::reverse(str->begin(), str->end());
}

void Interface::do_conv() {
  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i].first == "mute") {
      factory.add<Muter>(std::to_string(i));
      Converter* mute = factory.get(std::to_string(i))(
          input_files[i], output_file, data[i].second.at(0),
          data[i].second.at(1));
      mute->convert();
      delete mute;

    } else {
      factory.add<Mixer>(std::to_string(i));
      Converter* mix = factory.get(std::to_string(i))(
          input_files[i], output_file, data[i].second.at(0),
          data[i].second.at(1));
      mix->convert();
      delete mix;
    }
  }
}

/*void Interface::call_mixer(unsigned long number) {
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
}*/