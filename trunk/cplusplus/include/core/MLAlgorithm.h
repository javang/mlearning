/* 
 * File:   MLAlgorithm.h
 * Author: javi
 *
 * Created on July 1, 2012, 8:04 PM
 */

#ifndef MLALGORITHM_H
#define	MLALGORITHM_H

namespace ml {
  namespace core {
    
  class MLAlgorithm {
public:
  virtual ~MLAlgorithm() {};
  
  virtual void show_algorithm_information() const = 0;
};


} // core
} // ml

#endif	/* MLALGORITHM_H */

