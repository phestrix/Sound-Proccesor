#ifndef CONVERTOR_ERRORS
#define CONVERTOR_ERRORS

#include <stdexcept>

class IncorrectConverterName : public std::invalid_argument
{
public:
    explicit IncorrectConverterName(const std::string & converter_name);
};

#endif