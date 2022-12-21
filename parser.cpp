#include "parser.hpp"

#include <stdio.h>

#include <cstring>
#include <iostream>

// defalut constructor
Parser::Parser(FILE* file_in, FILE* file_out) {
  in = file_in;

  FILE* tmp = file_out;
  byte_after_data_out = parse(tmp);
  out = fopen("output.wav", "wb");

  char* data = (char*)malloc(20);
  while (fread(data, 1, 20, tmp) > 0) {
    fwrite(data, 1, 20, out);
  }

  byte_after_data_in = parse(in);
  fclose(tmp);
}

// constructor if no out file
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

// parsing header of WAV file
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

// for mix need to copy data from one stream
// and paste it to another
// in the same place
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
