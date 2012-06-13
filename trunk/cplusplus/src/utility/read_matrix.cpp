
#include "utility/eigen_helper.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::size_t read_buffer(std::istream &is, Chars &buffer ) {
  is.read( &buffer[0], buffer.size());
  return is.gcount();
}

std::size_t count_lines(const Chars &chars) {
  std::size_t lines = 0;
  for(std::size_t i = 0; i < chars.size(); ++i) 
    if(chars[i] == '\n') ++lines;
  return lines;
}
  
std::size_t count_lines(const String &filename) {
  std::ifstream fh(filename);
  if(! fh.good()) {
    fh.close();
    throw std::invalid_argument("Problem opening file");
  }
  std::size_t buffer_size = 1024 * 1024; 
  Chars buffer(buffer_size);
  std::size_t lines = 0;
  while(read_buffer(fh, buffer) != 0) {
    lines += count_lines(buffer);
  }
  fh.close();
  return lines;
}


