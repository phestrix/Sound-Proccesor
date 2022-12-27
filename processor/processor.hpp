#ifndef PROCESSOR
#define PROCESSOR
#include <string>
#include <vector>
#include "../cfg_parser/cfg_parser.hpp"
#include "../convertors/convertors_interface.hpp"
#include "../wav/reader.hpp"
#include "../wav/writer.hpp"

using WAVReaderVector = std::vector<WAVReader>;
using ConverterVector = std::vector<ConverterPtr>;

class Processor{
  private:
  std::string m_config_file;
  std::string m_output_file;
  std::vector<std::string> m_input_files;

  ConverterVector CreatePipeline(ConfigParser& config);
  FileLinks GetFileLinks(const ConverterVector& pipeline);
  WAVReaderVector OpenWAVReaders(const FileLinks& file_links);
  bool UpdateSampleVector(WAVReaderVector& wav_reader_vector, SampleVector& buf);

  public:
  Processor(std::string config_file, std::string output_file, std::vector<std::string> input_files);
  void Convert();
};


#endif