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
  m_additional_file_link = std::stoi(params[0].substr(1));
  m_start_second = std::stoi(params[1]);
}

void MixConverter::Process(SampleBuffer& buf, const SampleVector& default_samples) {
  if (m_current_second >= m_start_second) {
    for (int i = 0; i < buf.size(); ++i) {
      buf[i] = (buf[i] / 2) + (default_samples[m_additional_file_link][i] / 2);
    }
    ++m_current_second;
  }
}

FileLinks MixConverter::GetFileLinks() {
  return {0, m_additional_file_link};
}