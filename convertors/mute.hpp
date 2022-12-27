#ifndef MUTE
#define MUTE

#include "convertors_interface.hpp"

/// @brief Converter to mute interval in wav file
class MuteConverter : public ConverterInterface {
 public:
  explicit MuteConverter(ConverterParams params);
  ~MuteConverter() override = default;
  void Process(SampleBuffer& buf, const SampleVector& default_samples) override;
  FileLinks GetFileLinks() override;

 private:
  int m_start_second = 0;
  int m_current_second = 0;
  int m_end_second = 0;
};

#endif