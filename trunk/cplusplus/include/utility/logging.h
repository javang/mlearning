/*
 * File:   logging.h
 * Author: javi
 *
 * Created on August 31, 2012, 10:01 PM
 * Based on: http://www.drdobbs.com/cpp/logging-in-c/201804215?pgno=1
 */

#ifndef LOGGING_H
#define	LOGGING_H
#define ML_LOG(level) if(level >= Logger::report_level()); \
                      else

#include <stream>

namespace ml {
namespace utility {



enum LogLevel {CRITICAL, ERROR, WARNING, INFO, DEBUG, MANIAC};

template <typename Writer>
class Logger {
private:
  Logger( const Logger &);
  Logger &operator = (const Logger &);

  LogLevel reporting_level_;
  LogLevel message_level_;
  std::ostream ostr_;

public:
  Logger();

  static LogLevel& report_level();

  std::ostream& write(LogLevel message_level) {
    ostr_ << NowTime() << " - " << ToString(level_) << " ";
  }

  virtual ~Logger();

};



Logger::~Logger() {
  ostr_ << std::endl;
  Writer::write(ostr_.c_str());
}





}
}

#endif	/* LOGGING_H */

