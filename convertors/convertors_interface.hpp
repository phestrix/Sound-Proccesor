#ifndef INTERFACE
#define INTERFACE

#include <cstdint>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "../wav/types.hpp"

using SampleVector = std::vector<SampleBuffer>;
using ConverterParams = std::vector<std::string>;
using ConverterCommand = std::vector<std::string>;
using FileLinks = std::set<int>;

class ConverterInterface;
using ConverterPtr = std::unique_ptr<ConverterInterface>;

class ConverterInterface {
 public:
  virtual ~ConverterInterface() = default;
  virtual void Process(SampleBuffer& working_sample, const SampleVector& default_samples) = 0;
  virtual FileLinks GetFileLinks() = 0;
  static ConverterPtr Create(ConverterCommand converter_command);
};

#endif