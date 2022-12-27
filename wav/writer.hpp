#ifndef WRITER
#define WRITER

#include <fstream>
#include <string>

#include "types.hpp"

class WAVWriter {
 public:
  WAVWriter() = default;
  explicit WAVWriter(std::string file_path);
  ~WAVWriter();
  void Open(std::string file_path);
  void WriteSample(SampleBuffer sample_buffer);

 private:
  std::ofstream m_fout;
  std::string m_file_path;

  void WriteHeader();
  void FixHeader();
};

#endif
