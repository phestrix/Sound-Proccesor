#ifndef DOUBLE
#define DOUBLE
#include "convertors_interface.hpp"

class DoubleConverter : public ConverterInterface{
  private:
  int m_start_second = 0;
  int m_current_second = 0;
  int m_end_second = 0;
  
  public:
  explicit DoubleConverter(ConverterParams params);
  ~DoubleConverter() override = default;
  void Process(SampleBuffer& buf, const SampleVector& default_sample);
  FileLinks GetFileLinks();
};

#endif