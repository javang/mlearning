

#ifndef ERROR_H
#define ERROR_H

#include "core/definitions.h"
#include <exception>
#include <stdexcept>

class WrongParent: public std::runtime_error {
  String msg_;
public:
  WrongParent(const char *msg) throw(): std::runtime_error(msg) {};

//  const char *what() const throw() {
//    return msg_.c_str();
//  }
  virtual ~WrongParent() throw() {};
};


class ValueError: public std::runtime_error {
  String msg_;
public:
  /**
   * @param msg Message that the function what will return
   */
  ValueError(const char *msg) throw(): std::runtime_error(msg) {};

  virtual ~ValueError() throw() {};
  
  const char *what() const throw() {
    return msg_.c_str();
  }
};

class SizeError: public std::logic_error {
  String msg_;
public:
  /**
   * @param msg Error related with size of containers, matrices, or input
   */
  SizeError(const char *msg) throw(): std::logic_error(msg) {};

  virtual ~SizeError() throw() {};
  
  const char *what() const throw() {
    String msg = "SizeError: " + msg_;
    return msg.c_str();
  }
};


#endif  /* ERROR_H */

