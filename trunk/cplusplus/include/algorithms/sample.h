/* 
 * File:   sample.h
 * Author: javi
 *
 * Created on May 7, 2012, 7:22 PM
 */

#ifndef SAMPLE_H
#define	SAMPLE_H

#include "core/definitions.h"
/**
 * Return sample of integers from (1,n_values). The number of elements in the
 * sample is also random
 * @param n_values
 * @return A vector with the values in the sample
 */
Ints get_random_sample(unsigned long n_values);

#endif	/* SAMPLE_H */

