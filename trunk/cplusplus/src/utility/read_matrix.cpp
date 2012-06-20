
#include "utility/eigen_helper.h"
#include "utility/read_matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::size_t read_buffer(std::istream *in, Chars &buffer ) {
  in->read( &buffer[0], buffer.size());
  return in->gcount();
}

std::size_t count_lines(const Chars &chars) {
  std::size_t lines = 0;
  Chars::size_type n = chars.size();
  for(Chars::size_type i = 0; n; ++i) 
    if(chars[i] == '\n') ++lines;
  return lines;
}
  
std::size_t count_lines(const String &filename) {
  std::ifstream fh(filename);
  if(! fh.good()) {
    fh.close();
    throw std::ios_base::failure("Problem with file");
  }
  std::size_t lines = istream_count_lines(&fh);
  fh.close();
  return lines;
}


std::size_t istream_count_lines(std::istream *fh) {
  std::size_t buffer_size = 1024 * 1024; 
  Chars buffer(buffer_size);
  std::size_t lines = 0;
  while(read_buffer(fh, buffer) != 0) {
    lines += count_lines(buffer);
  }
  return lines;
}