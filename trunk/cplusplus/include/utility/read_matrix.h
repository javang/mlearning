/* 
 * File:   read_matrix.h
 * Author: javi
 *
 * Created on June 12, 2012, 5:52 PM
 */

#ifndef READ_MATRIX_H
#define	READ_MATRIX_H

#include <fstream>

template<typename T>
Matrix<T, Dynamic, Dynamic> read_matrix(const String &fn) {
  std::size_t rows = count_lines(fn);
  fh = std::ifstream(fn , std::ios_base::in );
  if(!fh.good()) {
    fh.close();
    throw std::invalid_argument("Problem opening file");
  }
  // TODO
  fh.close();
}


/**
 * Read a chunk of characters from a stream
 * @param is input stream
 * @param buffer vector of characters. Its size determines the maximum number of
 * characters read.
 * @return the number of characters read
 */
std::size_t read_buffer(std::istream &is, Chars &buffer );

/**
 * Count the number of lines in a set of characters
 * @param chars
 * @return 
 */
std::size_t count_lines(const Chars &chars);

/**
 * Count the number of lines in a file. Uses a buffer for speed
 * @param filename Name of the file
 * @return The number of lines in the file
 */
std::size_t count_lines(const String &filename);

#endif	/* READ_MATRIX_H */

