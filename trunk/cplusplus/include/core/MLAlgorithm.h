/* 
 * File:   MLAlgorithm.h
 * Author: javi
 *
 * Created on July 1, 2012, 8:04 PM
 */

#ifndef MLALGORITHM_H
#define	MLALGORITHM_H


class MLAlgorithm {
public:
  virtual ~MLAlgorithm() {};
  
  virtual void show_algorithm_information() const = 0;
};

#endif	/* MLALGORITHM_H */

