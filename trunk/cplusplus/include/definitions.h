/* 
 * File:   definitions.h
 * Author: javi
 *
 * Created on March 25, 2012, 9:30 PM
 */

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <vector>
#include <utility>
#include <set>
#include <string>
#include <unordered_map>

namespace ml {

typedef std::vector<int> Ints;
typedef std::vector<bool> Bools;
typedef std::vector<double> Doubles;
typedef std::vector<char> Chars;
typedef std::pair<int, int> IntPair;
typedef std::vector<IntPair > InPairs;
typedef std::set<int> IntsSet;
typedef std::string String;
typedef std::vector< String > Strings;
typedef std::unordered_map<int, int> Hash;

} // ml

#endif	/* DEFINITIONS_H */

