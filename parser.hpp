#ifndef PARSER
#define PARSER
#include <bitset>
#include <fstream>
#include <string>
#include <vector>

struct WAVheader {
    char chunk_id[4];

    unsigned int chunk_size;

    char format[4];

    char subchunk1_id[4];

    unsigned int subchunk1_size;

    unsigned short audio_format;

    unsigned short num_channels;

    unsigned int sample_rate;

    unsigned int byte_rate;  // bytes per second

    unsigned short block_align;

    unsigned short bits_per_sample;

    char subchunk2_id[4];

    unsigned int subchunk2_size;  // next bytes from 44 is samples
    /*
    if want to mute for 1 sec, than mute byte_rate * 1
    */
  };

class Parser {
 private:
  std::ofstream output_file;
  std::ifstream input_file;
  unsigned int bytes_sec_s;
  unsigned int bytes_sec_e;
  unsigned int byte_after_data;


  WAVheader* header;
  bool find_data_in_header();
  bool check_input();
  bool check_args(unsigned int* shift, unsigned int* bytes_to_change);

 public:
  Parser(std::string filename_in, std::string filename_out);
  Parser(std::string filename_in);
  ~Parser();
  unsigned int get_bytes_per_second();
  size_t get_eof_byte();
  void mute_samples(unsigned int* shift,
                    unsigned int* bytes_to_change);  // mute
  void copy_samples(unsigned int* shift,
                    unsigned int* bytes_to_change);  // copy
};

#endif