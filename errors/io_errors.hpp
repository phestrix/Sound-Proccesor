#ifndef IO_ERRORS
#define IO_ERRORS

#include <ios>

class FileNotOpen : public std::ios_base::failure {
 public:
  explicit FileNotOpen(std::string file_path);
};

class FileNotWrite : public std::ios_base::failure {
 public:
  explicit FileNotWrite(std::string file_path);
};

#endif