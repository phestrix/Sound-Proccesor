#include "cl_parser.hpp"

#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iomanip>
#include <iostream>

namespace po = boost::program_options;
namespace pt = boost::property_tree;

static void PrintConverterDesc() {
  pt::ptree ptree;
  pt::read_json(CONVERTERS_CONFIG_FILE, ptree);
  std::cout << "Available Converters: " << std::endl;
  for (const auto& converter_info : ptree.get_child("Converters")) {
    std::cout << " " << std::setw(48) << std::left << converter_info.second.get<std::string>("Command") << converter_info.second.get<std::string>("Description") << std::endl;
  }
  std::cout << std::endl;
}

bool GetOptions(int argc, char** argv, Options& opts) {
  po::options_description opts_desc("General options");
  opts_desc.add_options()("help, h", "Show options description")("config, c", po::value<std::string>(&opts.m_config_file)->required(), "Configuration file")("output,O", po::value<std::string>(&opts.m_output_file)->required(), "Output file")("input,I", po::value<std::vector<std::string>>(&opts.m_input_files)->multitoken()->required(), "Input files");

  po::variables_map vm;
  po::parsed_options parsed_options = po::command_line_parser(argc, argv).options(opts_desc).run();
  store(parsed_options, vm);
  if (vm.count("help")) {
    PrintConverterDesc();
    std::cout << opts_desc << std::endl;
    return false;
  }
  notify(vm);
  return true;
}