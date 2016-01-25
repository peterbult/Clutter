//
//  Convert.h
//  Custom Headers
//
//  Created by Peter on 20-11-09.
//  Copyright 2009 P.M. Bult. All rights reserved.
//
//  Version 1.1
//

#ifndef convert_h
#define convert_h

#include <iostream>
#include <sstream>

#pragma mark toString() method
// Inline variant, no validity check
template <class T>
std::string toString(T number) {
	std::stringstream strs;
	strs << number;
	return strs.str();
}
// Stored variant, with validity check
template <class T>
bool toString(const T& val, std::string &str) {
    std::stringstream strs;
    if ( !(strs << val).fail() ) {
        str = strs.str();
        return true;
    } else
        return false;
}

#pragma mark fromString() method
// Inline variant, no validity check
template <class T>
T fromString(const std::string& str) {
    std::istringstream iss(str);
    T number;
    iss >> std::dec >> number;
    return number;
}
// Stored variant, with validity check
template <class T>
bool fromString(const std::string& str, T &val) {
    std::istringstream iss(str);
    return !(iss >> std::dec >> val).fail();
}

#endif /* convert_h */

