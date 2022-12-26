#ifndef MUTE
#define MUTE

#include "convertors_interface.hpp"

class MuteConverter : public ConverterInterface {
 public:
  explicit MuteConverter(ConverterParams params);
  ~MuteConverter() override = default;
  void Process(SampleBuffer& buf, const SampleVector& default_samples) override;
  FileLinks GetFileLinks() override;

 private:
  int start_second_ = 0;
  int current_second_ = 0;
  int end_second_ = 0;
};

#endif