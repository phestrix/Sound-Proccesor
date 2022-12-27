#ifndef TYPES
#define TYPES

#include <array>
#include <cstdint>

const uint32_t RIFF = 0x46464952;
const uint32_t WAVE = 0x45564157;
const uint32_t FMT_ = 0x20746d66;
const uint32_t DATA = 0x61746164;

const uint16_t AUDIO_FORMAT_PCM = 0x0001;
const uint16_t NUM_CHANNELS = 1;
const uint32_t SAMPLING_RATE = 44100;
const uint16_t BITS_PER_BYTE = 8;
const uint16_t BITS_PER_SAMPLE = BITS_PER_BYTE * sizeof(int16_t);
const uint16_t BLOCK_ALIGN = BITS_PER_SAMPLE * NUM_CHANNELS / BITS_PER_BYTE;
const uint32_t BYTE_RATE = BLOCK_ALIGN * SAMPLING_RATE;

struct ChunkHeader {
  uint32_t m_ID;
  uint32_t m_size;
};

using FormatType = uint32_t;

struct FMTChunkData {
  uint16_t m_audio_format = AUDIO_FORMAT_PCM;    // Audio format
  uint16_t m_num_channels = NUM_CHANNELS;        // Channels number
  uint32_t m_sampling_rate = SAMPLING_RATE;      // Sampling rate in Hz
  uint32_t m_byte_rate = BYTE_RATE;              // Bytes number transmitted per second of playback
  uint16_t m_block_align = BLOCK_ALIGN;          // Bytes number per sample
  uint16_t m_bits_per_sample = BITS_PER_SAMPLE;  // Bits number in the sample (depth)
};

using Sample = int16_t;
using SampleBuffer = std::array<Sample, SAMPLING_RATE>;

#endif