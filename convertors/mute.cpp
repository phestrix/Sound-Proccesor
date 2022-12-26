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

  start_second_ = std::stoi(params[0]);
  end_second_ = std::stoi(params[1]);

  if (start_second_ > end_second_)
    throw std::invalid_argument("Incorrect interval");
}

void MuteConverter::Process(SampleBuffer& buf, const SampleVector& default_samples) {
  if (current_second_ >= start_second_ &&
      current_second_ <= end_second_)
    buf.fill(0);
  ++current_second_;
}

FileLinks MuteConverter::GetFileLinks() {
  return {0};
}