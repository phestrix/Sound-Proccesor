#include "reader.hpp"

#include "../errors/io_errors.hpp"
#include "errors.hpp"
#include "writer.hpp"

WAVReader::WAVReader(std::string file_path) {
  Open(std::move(file_path));
}

void WAVReader::Open(std::string file_path) {
  m_file_path = std::move(file_path);

  // check file extension
  if (m_file_path.find(".wav") == std::string::npos)
    throw IncorrectExtension(m_file_path);

  // file opening
  m_fin.open(m_file_path, std::ios_base::binary);
  if (!m_fin.good()) {
    throw FileNotOpen(m_file_path);
  }

  ReadHeader();
}

bool WAVReader::ReadSample(SampleBuffer &sample_buffer) {
  m_fin.read((char *)&sample_buffer[0], sizeof(sample_buffer[0]) * sample_buffer.size());
  if (m_fin.gcount() == 0) {
    sample_buffer.fill(0);
  }
  return (bool)m_fin.gcount();
}

void WAVReader::SearchChunk(uint32_t chunk_ID) {
  ChunkHeader chunk_header{};
  while (true) {
    m_fin.read((char *)&chunk_header, sizeof(chunk_header));
    if (!m_fin.good()) {
      throw ChunkNotFound(m_file_path, chunk_ID);
    }
    if (chunk_header.m_ID == chunk_ID) {
      break;
    }
    m_fin.seekg(chunk_header.m_size, std::fstream::cur);
  }
}

void WAVReader::ReadHeader() {
  // check RIFF header
  ChunkHeader RIFF_header{};
  m_fin.read((char *)&RIFF_header, sizeof(RIFF_header));

  if (!m_fin.good() || RIFF_header.m_ID != RIFF) {
    throw IncorrectRIFFHeader(m_file_path);
  }

  // check format type
  FormatType format_type;
  m_fin.read((char *)&format_type, sizeof(format_type));
  if (!m_fin.good() || format_type != WAVE) {
    throw IncorrectFormatType(m_file_path);
  }

  // check FMT data
  SearchChunk(FMT_);
  FMTChunkData fmt_chunk_data;
  m_fin.read((char *)&fmt_chunk_data, sizeof(fmt_chunk_data));
  if (!m_fin.good()) {
    throw IncorrectFormatData(m_file_path);
  }

  if (fmt_chunk_data.m_audio_format != AUDIO_FORMAT_PCM) {
    throw IncorrectAudioFormat(m_file_path);
  }
  if (fmt_chunk_data.m_num_channels != 1) {
    throw IncorrectChannelsNumber(m_file_path);
  }
  if (fmt_chunk_data.m_bits_per_sample != 16) {
    throw IncorrectSampleBits(m_file_path);
  }
  if (fmt_chunk_data.m_sampling_rate != SAMPLING_RATE) {
    throw IncorrectSamplingRate(m_file_path);
  }

  // find DATA data
  SearchChunk(DATA);
}