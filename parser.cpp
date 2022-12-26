#include "parser.hpp"

#include <stdio.h>

#include <cstring>
#include <iostream>

/// @brief defalut constructor
/// @param file_in file for input, where to read
/// @param file_out file for ouput, where to write
Parser::Parser(FILE* file_in, FILE* file_out) {
  in = file_in;

  FILE* tmp = file_out;
  byte_after_data_out = parse(tmp);

  byte_after_data_in = parse(in);
  fclose(tmp);
}

/// @brief constructor if no out file
Parser::Parser(FILE* filename) {
  in = filename;
  char* data = (char*)malloc(20);

  out = fopen("out.wav", "wb");
  while (fread(data, 20, 1, in) > 0) {
    fwrite(data, 20, 1, out);
  }
  parse(in);
  free(data);
}

// destructor
Parser::~Parser() {
  if (in) fclose(in);
  if (out) fclose(out);
}

/// @brief parsing header of WAV file
int Parser::parse(FILE* file) {
  int res = 0;
  FILE* f = file;
  fseek(f, 0, SEEK_SET);
  fread(&header, sizeof(header), 1, f);
  fseek(f, header.fLen - 16,
        SEEK_CUR);  // skip wExtraFormatBytes & extra format bytes
  chunk_t chunk;
  while (true) {  // go to data chunk

    fread(&chunk, sizeof(chunk), 1, f);
    if (*(int*)&chunk.id == 0x61746164) {
      res = ftell(f) + 8;
      break;
    }

    fseek(f, chunk.size, SEEK_CUR);  // skip chunk data bytes
  }
  fseek(f, 0, SEEK_SET);
  return res;
}

/// @brief  mix need to copy data from one stream,  paste it to another in the same place
/// @param start second when start mixing
/// @param end second when end mixing
int Parser::mix(int start, int end) {
  if (!in) {
    return OPEN_ERROR;
  }

  if (!out) {
    return OPEN_ERROR;
  }

  if (fseek(in, start + byte_after_data_in, SEEK_SET)) {
    return SEEK_ERROR;
  }

  if (fseek(out, start + byte_after_data_out, SEEK_SET)) {
    return SEEK_ERROR;
  }

  for (int i = start; i < end * header.nAvgBytesPerSec; ++i) {
    int a = fgetc(in);
    fputc(a, out);
  }

  return SUCCESS;
}
/// @brief func that mute some seconds, xor some bytes, based on average bytes per second chunk
/// @param start second where to start muting
/// @param end second where to end muting
int Parser::mute(int start, int end) {
  if (!out) {
    return OPEN_ERROR;
  }

  if (fseek(out, byte_after_data_in + start, SEEK_SET)) {
    return SEEK_ERROR;
  }

  for (int i = start; i < end * header.nAvgBytesPerSec; ++i) {
    fputc(0, out);
  }

  return SUCCESS;
}
