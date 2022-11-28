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
      "input,i", po::value<std::string>(&input_filename)->default_value("input1.wav"),
      "set input files")("output,o",
                         po::value<std::string>(&output_filename)->default_value("output.wav"),
                         "set output files")(
      "config", po::value<std::string>(&config_filename)->default_value("config.txt"),
      "set config file");

  po::variables_map vm;
  po::parsed_options parsed = po::command_line_parser(ac, av)
                                  .options(description)
                                  .allow_unregistered()
                                  .run();
  po::store(parsed, vm);
  po::notify(vm);
  
  /*
   */
  return 0;
}