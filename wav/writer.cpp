#include "writer.hpp"

#include "errors.hpp"
#include "../errors/io_errors.hpp"

WAVWriter::WAVWriter(std::string file_path) {
  Open(std::move(file_path));
}

WAVWriter::~WAVWriter() {
  FixHeader();
}

void WAVWriter::Open(std::string file_path) {
  m_file_path = std::move(file_path);

  // file opening
  m_fout.open(m_file_path, std::ios_base::binary);
  if (!m_fout.good())
    throw FileNotOpen(m_file_path);

  WriteHeader();
}

void WAVWriter::WriteSample(SampleBuffer sample_buffer) {
  m_fout.write((const char *)&sample_buffer[0], sizeof(sample_buffer[0]) * sample_buffer.size());

  if (!m_fout.good())
    throw FileNotWrite(m_file_path);
}

void WAVWriter::WriteHeader() {
  // write RIFF header
  ChunkHeader RIFF_header = {
      RIFF,
      0};

  m_fout.write((const char *)&RIFF_header, sizeof(RIFF_header));

  // write format type
  FormatType format_type = WAVE;
  m_fout.write((const char *)&format_type, sizeof(format_type));

  // write FMT header
  ChunkHeader FMT_header = {
      FMT_,
      sizeof(FMTChunkData)};

  m_fout.write((const char *)&FMT_header, sizeof(FMT_header));

  // write FMT data
  FMTChunkData fmt_data;
  m_fout.write((const char *)&fmt_data, sizeof(fmt_data));

  // write DATA header
  ChunkHeader data_header = {
      DATA,
      0};
  m_fout.write((const char *)&data_header, sizeof(data_header));
}

void WAVWriter::FixHeader() {
  // get file size
  m_fout.seekp(0,
              std::ios_base::end);
  uint32_t file_size = m_fout.tellp();

  // get RIFF header size position
  m_fout.seekp(sizeof(RIFF), std::ios_base::beg); // RIFF ID size
  file_size -= sizeof(ChunkHeader);  // RIFF header
  m_fout.write((const char *)&file_size, sizeof(file_size));

  // get DATA header size position
  file_size -= sizeof(FormatType)         // Format type size
               + sizeof(ChunkHeader)      // FMT chunk header size
               + sizeof(FMTChunkData)     // FMT chunk data size
               + sizeof(ChunkHeader);     // DATA chunk data size
  m_fout.seekp(sizeof(ChunkHeader)         // RIFF header size
                  + sizeof(FormatType)    // Format type size
                  + sizeof(ChunkHeader)   // FMT header size
                  + sizeof(FMTChunkData)  // FMT data size
                  + sizeof(DATA),         // DATA ID size
              std::ios_base::beg);
  m_fout.write((char *)&file_size,
              sizeof(file_size));
}