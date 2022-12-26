#include "interface.hpp"

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

Interface::~Interface() {

  if (output) {
    fclose(output);
  }

  for (const auto& it : in_files) {
    if (it) {
      fclose(it);
    }
  }

}

void Interface::do_conv() {
  if (!open_files()) {
    std::throw_with_nested(std::runtime_error("couldn't open files\n"));
  }

  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i].first == "mute") {
      factory.add<Muter>(std::to_string(i));

      Converter* mute = factory.get(std::to_string(i))(in_files[i], output, data[i].second.at(0), data[i].second.at(1));

      mute->convert();
      delete mute;

    } else {
      factory.add<Mixer>(std::to_string(i));

      Converter* mix = factory.get(std::to_string(i))(
          in_files[i], output, data[i].second.at(0),
          data[i].second.at(1));

      mix->convert();
      delete mix;
    }
  }
}

void Interface::set_data(
    std::vector<std::pair<std::string, std::vector<int>>> d) {
  this->data = d;
}

bool Interface::open_files() {
  for (const auto& it : input_files) {
    in_files.push_back(fopen(it.c_str(), "rb"));
    if (!in_files.back()) {
      return false;
    }
  }
  if (!(output = fopen(output_file.c_str(), "wb"))) return false;

  return true;
}