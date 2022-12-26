#include "mix.hpp"

#include <algorithm>
#include <stdexcept>

static bool IsNumber(const std::string& str) {
  return std::all_of(str.cbegin(), str.cend(), [](char sym) { return std::isdigit(sym); });
}

static bool IsLink(const std::string& str) {
  return str.size() > 1 && str[0] == '$' && IsNumber(str.substr(1));
}

MixConverter::MixConverter(ConverterParams params) {
  if (params.size() != 2) {
    throw std::invalid_argument("Incorrect number of params");
  }
  if (!IsLink(params[0])) {
    throw std::invalid_argument("Incorrect file link");
  }
  if (!IsNumber(params[1])) {
    throw std::invalid_argument("Incorrect numbers");
  }
  additional_file_link_ = std::stoi(params[0].substr(1));
  start_second_ = std::stoi(params[1]);
}

void MixConverter::Process(SampleBuffer& buf, const SampleVector& default_samples) {
  if (current_second_ >= start_second_) {
    for (int i = 0; i < buf.size(); ++i) {
      buf[i] = (buf[i] / 2) + (default_samples[additional_file_link_][i] / 2);
    }
    ++current_second_;
  }
}

FileLinks MixConverter::GetFileLinks() {
  return {0, additional_file_link_};
}