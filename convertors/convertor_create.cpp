#include <stdexcept>

#include "convertors_interface.hpp"
#include "double.hpp"
#include "mix.hpp"
#include "mute.hpp"

ConverterPtr ConverterInterface::Create(ConverterCommand converter_comand) {
  std::string converter_name = converter_comand[0];
  converter_comand.erase(converter_comand.cbegin());
  if (converter_name == "mute") {
    return std::make_unique<MuteConverter>(converter_comand);
  } else if (converter_name == "mix") {
    return std::make_unique<MixConverter>(converter_comand);
  } else if (converter_name == "double") {
    return std::make_unique<DoubleConverter>(converter_comand);
  }

  else {
    throw std::invalid_argument(converter_name + " : Convertor wasn't exist");
  }
}