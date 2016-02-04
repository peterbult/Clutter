// Utils.cpp | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#include <cctype>       // Loads std::isalpha() 
                        // for alphabetic character test

#include "Utils.h"

namespace Clutter {
    namespace Utils {

        //
        // Test if a string is a flag type
        //
        bool isFlag( std::string arg )
        {
            // Test length
            if ( arg.size() < 2 ) return false;

            // Test flag identifier
            if ( arg[0] == '-' && isalpha(arg[1]) ) return true;  // '-3' is treated as a number
            if ( arg[0] == '-' && arg[1] == '-'   ) return true;  // e.g. '--label'

            // All tests failed
            return false;
        }

        // 
        // Test if a string is a value type
        //
        bool isValue( std::string arg )
        {
            // Test by inversion
            return !isFlag(arg);
        }
        
        // 
        // Retrieve the type of the string
        //
        arg_t getArgType( std::string arg )
        {
            // Check if the argument is well defined
            if ( arg.empty() )                                          throw "Bad argument";
            if ( arg.size() == 1 && arg[0] == '-' )                     throw "Bad flag";
            if ( arg.size() == 2 && arg[0] == '-' && arg[1] == '-' )    throw "Bag flag";

            // Check arg type
            if ( isFlag( arg ) )    return arg_t::FLAG;
            else                    return arg_t::VALUE;
        }
    }
}
