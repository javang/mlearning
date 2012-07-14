/* 
 * File:   types.h
 * Author: javi
 *
 * Created on June 20, 2012, 10:51 AM
 */

#ifndef TYPES_H
#define	TYPES_H

#include <vector>

namespace ml {
  
/**
 * A feature can be categorical or continuous
 */
enum VariableType {
  CATEGORICAL, CONTINUOUS
};
typedef std::vector<VariableType> VariableTypes;

} // ml    

#endif	/* TYPES_H */

