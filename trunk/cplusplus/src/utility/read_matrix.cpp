
#include "utility/eigen_helper.h"
#include <ifstream>

template<typename T>
Matrix<T, Dynamic, Dynamic> read_matrix(const String &fn) {
  std::size_t rows = count_lines(fn);
  fh = std::ifstream(fn , std::ios_base::in );
  if(!fh.good()) {
    fh.close();
    throw std::invalid_argument("Problem opening file");
  }
**************  
  
  fh.close();
}

/**
 * Read a chunk of characters from a stream
 * @param is input stream
 * @param buffer vector of characters. Its size determines the maximum number of
 * characters read.
 * @return the number of characters read
 */
std::size_t read_buffer(std::istream &is, Chars &buffer ) {
  is.read( &buff[0], buff.size());
  return is.gcount();
}

/**
 * Count the number of lines in a set of characters
 * @param chars
 * @return 
 */
std::size_t count_lines(const Chars &chars) {
  std::size_t lines = 0;
  for(std::size_t i = 0; i < chars.size(); ++i) 
    if(chars[i] == "\n") ++lines;
  return lines;
}
  
/**
 * Count the number of lines in a file. Uses a buffer for speed
 * @param filename Name of the file
 * @return The number of lines in the file
 */
std::size_t count_lines(const String &filename) {
  fh = std::ifstream(filename);
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


