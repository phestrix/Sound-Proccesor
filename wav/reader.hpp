#ifndef READER
#define READER

#include <fstream>
#include <string>

#include "types.hpp"

class WAVReader {
 public:
  WAVReader() = default;
  explicit WAVReader(std::string file_path);
  ~WAVReader() = default;
  void Open(std::string file_path);
  bool ReadSample(SampleBuffer& sample_buffer);

 private:
  std::ifstream m_fin;
  std::string m_file_path;

  void SearchChunk(uint32_t chunk_ID);
  void ReadHeader();
};

#endif