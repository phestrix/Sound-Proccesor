#include "helper.hpp"
#include <string>
#include <iostream>

Helper::Helper() {
  std::string info = "for convertation you need to write your commands in \"config.txt\" next step is choose files you want to convert, you need to rename them to input1.wav, input2.wav,...";
  std::cout << info;
}

Helper::~Helper() {}
