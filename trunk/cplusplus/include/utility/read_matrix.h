/* 
 * File:   read_matrix.h
 * Author: javi
 *
 * Created on June 12, 2012, 5:52 PM
 */

#ifndef READ_MATRIX_H
#define	READ_MATRIX_H

#include <fstream>
#include "core/definitions.h"
#include "utility/errors.h"
#include "utility/eigen_helper.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>


/**
 * Converts a string to the type used as template parameter
 * @param s
 * @return the value contained in the string
 */
template <typename T>
class ConvertTo {
public:
  T operator()(const String &s) {
    T value;
    std::istringstream is(s);
    is >> value;
    return value;
  }
};



        
/**
 * Read a chunk of characters from a stream
 * @param is input stream
 * @param buffer vector of characters. Its size determines the maximum number of
 * characters read.
 * @return the number of characters read
 */
std::size_t read_buffer(std::istream *is, Chars &buffer );

/**
 * Count the number of lines in a set of characters
 * @param chars
 * @param max_chars Maximum number of characters to read to count the lines
 * @return 
 */
std::size_t count_lines(const Chars &chars, std::size_t max_chars);



/**
 * Count the number of lines in the stream
 * @param fh
 * @return the number of lines
 */
std::size_t istream_count_lines(std::istream *fh);

/**
 * Count the number of lines in a file. Uses a buffer for speed
 * @param filename Name of the file
 * @return The number of lines in the file
 */
std::size_t count_lines(const String &filename);



/**
 * Reads an Eigen Matrix from a file. Resizes the matrix appropriately and
 * checks that all the rows have the same number of columns
 * @param fn name of the file
 * @param delimiters The characters used as delimiters. They can be more than
 * one
 * @return The matrix. The type of the matrix is specified by the template 
 * parameter
 */
template<typename T>
Matrix<T, Dynamic, Dynamic> read_matrix(const String &fn, 
                                        const String &delimiters) {
  Matrix<T, Dynamic, Dynamic> M;
  std::size_t rows = count_lines(fn);
  std::size_t cols = 0;
  std::size_t row = 0;
  
  std::ifstream fh(fn);
  String line;
  std::getline(fh, line);
  Strings words; 
  ConvertTo<T> converter;
  if(line.empty()) {
    M.resize(0,0);
    return M;
  } else {
    boost::split(words, line, boost::is_any_of(delimiters),
                boost::token_compress_on);
    cols = words.size();
    M.resize(rows, cols);
    row = 0;
    for (unsigned int j=0; j<cols; ++j) {
      M(row, j) = converter(words[j]);
    }
  }
  while(std::getline(fh, line)) {
    boost::split(words, line, boost::is_any_of(delimiters),
                boost::token_compress_on);
    if(words.size() != cols) {
      fh.close();
      String msg = "Error in the number of columns. Line: " + line;
      throw SizeError(msg.c_str());
    }
    ++row;
    for (unsigned int j=0; j < cols; ++j) {
      M(row, j) = converter(words[j]);
    }
  } 
}


#endif	/* READ_MATRIX_H */

