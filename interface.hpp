#ifndef INTERFACE
#define INTERFACE
#include "config_parser.hpp"
#include <fstream>
#include <vector>

class Interface {
  private:
  std::vector<std::ifstream> input_files;
  std::ofstream output_file;
  public:
  Interface(){
    
  }
 
};

#endif