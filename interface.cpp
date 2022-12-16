#include "interface.hpp"

#include <algorithm>

#include "config_parser.hpp"

Interface::Interface(std::vector<std::string> inputs) {
  for (size_t i = 0; i < inputs.size(); ++i) {
    if (inputs[i].find("config.txt") != std::string::npos) {
      CFG cfg;
      if (cfg.parse_args(inputs[i])) {
        throw std::invalid_argument("Something wrong in cfg file");
      }
      set_data(cfg.get_data());
    } else if (inputs[i].find("input") != std::string::npos) {
      input_files.push_back(inputs[i]);
    } else if (inputs[i].find("output") != std::string::npos) {
      output_file = inputs[i];
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
     // std::cout << "2" << std::endl;
      factory.add<Mixer>(std::to_string(i));
      Converter* mix = factory.get(std::to_string(i))(
          input_files[i], output_file, data[i].second.at(0),
          data[i].second.at(1));
      mix->convert();
      delete mix;
    }
  }
}

void Interface::set_data(
    std::vector<std::pair<std::string, std::vector<unsigned int>>> d) {
  this->data = d;
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