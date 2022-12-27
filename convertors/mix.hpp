#ifndef MIX
#define MIX

#include "convertors_interface.hpp"

/// @brief Converter to mix 2 wav files
class MixConverter : public ConverterInterface {
 public:
  explicit MixConverter(ConverterParams params);
  ~MixConverter() override = default;
  void Process(SampleBuffer &buf, const SampleVector& default_samples) override;
  FileLinks GetFileLinks() override;

 private:
  int m_start_second = 0;
  int m_current_second = 0;
  int m_additional_file_link = 0;
};

#endif