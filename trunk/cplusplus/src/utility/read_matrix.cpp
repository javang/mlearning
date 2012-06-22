
#include "utility/eigen_helper.h"
#include "utility/read_matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

std::size_t read_buffer(std::istream *in, Chars &buffer ) {
  in->read( &buffer[0], buffer.size());
  std::size_t n = in->gcount();
  buffer.resize(n);
  return n;
}

std::size_t count_lines(const Chars &chars, std::size_t max_chars) {
  std::size_t lines = 0;
  Chars::size_type n = std::min(chars.size(), max_chars);
  for(Chars::size_type i = 0; i < n; ++i) 
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
  std::size_t n_chars_read = -1;
  do {
    n_chars_read = read_buffer(fh, buffer);
    lines += count_lines(buffer, n_chars_read);
  } while(n_chars_read != 0);
  return lines;
}