#include "mute.hpp"

#include <algorithm>
#include <stdexcept>

static bool IsNumber(const std::string& str) {
  return std::all_of(str.cbegin(), str.cend(), [](char sym) { return std::isdigit(sym); });
}

static bool IsLink(const std::string& str) {
  return str.size() > 1 && str[0] == '$' && IsNumber(str.substr(1));
}

MuteConverter::MuteConverter(ConverterParams params) {
  if (params.size() != 2)
    throw std::invalid_argument("Wrong number of params");
  if (!IsNumber(params[0]))
    throw std::invalid_argument("Wrong first param");
  if (!IsNumber(params[1]))
    throw std::invalid_argument("Wrong second param");

  m_start_second = std::stoi(params[0]);
  m_end_second = std::stoi(params[1]);

  if (m_start_second > m_end_second)
    throw std::invalid_argument("Incorrect interval");
}

void MuteConverter::Process(SampleBuffer& buf, const SampleVector& default_samples) {
  if (m_current_second >= m_start_second && m_current_second <= m_end_second)
    buf.fill(0);
  ++m_current_second;
}

FileLinks MuteConverter::GetFileLinks() {
  return {0};
}