

#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>

class WrongParent: public std::runtime_error {
public:
  WrongParent(const char *msg) throw(): msg_(msg) {};
  const char *what() const throw() {
    std::string msg = "Only one parent per node is allowed";
    return msg.c_str();
  }
};


class ValueError: public std::runtime_error {
  std::string msg_;
public:
  /**
   * @param msg Message that the function what will return
   */
  ValueError(const char *msg) throw(): msg_(msg) {};
  virtual ~ValueError() throw() {};
  
  const char *what() const throw() {
    return msg_.c_str();
  }
};


#endif  /* ERROR_H */

