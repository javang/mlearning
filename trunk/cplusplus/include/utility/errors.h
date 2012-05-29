

#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>
#include <stdexcept>

class WrongParent: public std::runtime_error {
  std::string msg_;
public:
  WrongParent(const char *msg) throw(): std::runtime_error(msg) {};

//  const char *what() const throw() {
//    return msg_.c_str();
//  }
  virtual ~WrongParent() throw() {};
};


class ValueError: public std::runtime_error {
  std::string msg_;
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



#endif  /* ERROR_H */

