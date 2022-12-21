#ifndef PARSER
#define PARSER
#include <stdio.h>

#include <fstream>
#include <string>
#include <vector>

#define SUCCESS 0
#define OPEN_ERROR 1
#define MEM_ERROR 2
#define SEEK_ERROR 3
#define IO_ERROR 4

struct wav_header_t {
  char rId[4];  //"RIFF" = 0x46464952
  int rLen;     // 28 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes] +
                // sum(sizeof(chunk.id) + sizeof(chunk.size) + chunk.size)
  char wId[4];  //"WAVE" = 0x45564157
  char fId[4];  //"fmt " = 0x20746D66
  int fLen;     // 16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
  short wFormatTag;
  short nChannels;
  int nSamplesPerSec;
  int nAvgBytesPerSec;
  short nBlockAlign;
  short wBitsPerSample;
  //[short wExtraFormatBytes;]
  //[Extra format bytes]
};

struct chunk_t {
  char id[4];  //"data" = 0x61746164
  int size;
  // Chunk data bytes
};

class Parser {
 private:
  wav_header_t header;
  FILE* in;
  FILE* out;
  int byte_after_data_in;
  int byte_after_data_out;
  int parse(FILE* file);

 public:
  Parser(FILE* filename);
  Parser(FILE* file_in, FILE* file_out);
  ~Parser();
  int mute(int start, int end);
  int mix(int start, int end);
};

#endif