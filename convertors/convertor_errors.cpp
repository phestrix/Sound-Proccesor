#include "convertor_errors.hpp"

IncorrectConverterName::IncorrectConverterName(const std::string& converter_name) : std::invalid_argument(converter_name + " : Converter was not found") {}