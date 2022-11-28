#include <exception>
#include <iostream>
#include <iterator>

#include "boost/program_options.hpp"
#include "interface.hpp"

namespace po = boost::program_options;

int main(int ac, char* av[]) {
  std::string input_filename;
  std::string output_filename;
  std::string config_filename;

  po::options_description description("Command line options");
  description.add_options()("help,h", "show help page")(
      "input,i",
      po::value<std::string>(&input_filename)->default_value("input1.wav"),
      "set input files")(
      "output,o",
      po::value<std::string>(&output_filename)->default_value("output.wav"),
      "set output files")(
      "config",
      po::value<std::string>(&config_filename)->default_value("config.txt"),
      "set config file");

  po::variables_map vm;
  po::parsed_options parsed = po::command_line_parser(ac, av)
                                  .options(description)
                                  .allow_unregistered()
                                  .run();
  po::store(parsed, vm);
  po::notify(vm);

  std::string convert_mode;
  std::ifstream config;
  config.open(config_filename);
  unsigned start, end = 0;
  std::string stream_to_mix;
  std::string stream_to_convert;
  po::options_description config_description("Config options");
  config_description.add_options()(
      "convert,c", po::value<std::string>(&convert_mode)->default_value("mute"),
      "select convert mode")("start second", po::value<unsigned>(&start),
                             "start second")("end", po::value<unsigned>(&end),
                                             "end second")(
      "stream",
      po::value<std::string>(&stream_to_convert)->default_value(input_filename),
      "choose stream to convert")("stream to mix",
                                  po::value<std::string>(&stream_to_mix),
                                  "choose stream to mix");
  po::parse_config_file(config, config_description, false);

  /*
   */
  return 0;
}