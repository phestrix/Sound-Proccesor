#ifndef PARSER
#define PARSER
#include <bitset>
#include <fstream>
#include <string>
#include <vector>

class Parser {
 private:
  std::ofstream output_file;
  std::ifstream input_file;

  struct WAVheader {
    char chunk_id[4];

    unsigned chunk_size;

    char format[4];

    char subchunk1_id[4];

    unsigned subchunk1_size;

    unsigned short audio_format;

    unsigned short num_channels;

    unsigned long sample_rate;

    unsigned long byte_rate;  // bytes per second

    unsigned short block_align;

    unsigned short bits_per_sample;

    char subchunk2_id[4];

    unsigned long subchunk2_size;  // next bytes from 44 is samples
    /*
    if want to mute for 1 sec, than mute byte_rate * 1
    */
  };

  WAVheader* header;
  bool find_list_in_header();
  bool check_input();
  bool check_args(unsigned* shift, unsigned* bytes_to_change);

 public:
  Parser(std::string filename);
  ~Parser();
  unsigned long get_bytes_per_second();
  void mute_samples(unsigned* shift, unsigned* bytes_to_change);  // mute
  void copy_samples(unsigned* shift, unsigned* bytes_to_change);  // copy
};

#endif