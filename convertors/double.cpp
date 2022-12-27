#include "double.hpp"

#include <algorithm>
#include <iostream>

static bool IsNumber(const std::string& str) {
  return std::all_of(str.cbegin(), str.cend(), [](char sym) { return std::isdigit(sym); });
}

DoubleConverter::DoubleConverter(ConverterParams params) {
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

void DoubleConverter::Process(SampleBuffer& buf, const SampleVector& default_samples) {
  if (m_current_second >= m_start_second && m_current_second <= m_end_second) {
    for (int i = 0; i < buf.size() / 2; ++i)  buf[i] = buf[i * 2];
    for (int i = 0; i < buf.size() / 2; ++i)  buf[i] = buf[buf.size() / 2 + i];
    
  }
  ++m_current_second;
}

FileLinks DoubleConverter::GetFileLinks() {
  return {0};
}