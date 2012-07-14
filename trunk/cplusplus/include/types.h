/* 
 * File:   types.h
 * Author: javi
 *
 * Created on June 20, 2012, 10:51 AM
 */

#ifndef TYPES_H
#define	TYPES_H

#include <vector>

/**
 * A feature can be categorical or continuous
 */
enum VariableType {
  CATEGORICAL, CONTINUOUS
};
typedef std::vector<VariableType> VariableTypes;


#endif	/* TYPES_H */

