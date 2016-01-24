// 
// Utils.cpp
// Clutter
//
// Created by PM Bult on 24-01-2016
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.0
//

#include <cctype>       // Loads std::isalpha() 
                        // for alphabetic character test

#include "TagUtils.h"

namespace Clutter {
    namespace Utils {

        //
        // Test if a string is a tag type
        //
        bool isFlag( std::string tag )
        {
            // Test length
            if ( tag.size() < 2 ) return false;

            // Test flag identifier
            if ( tag[0] == '-' && isalpha(tag[1]) ) return true;  // '-3' is treated as a number
            if ( tag[0] == '-' && tag[1] == '-'   ) return true;  // e.g. '--label'

            // All tests failed
            return false;
        }

        // 
        // Test if a string is a value type
        //
        bool isLabel( std::string tag )
        {
            // Test by inversion
            return !isFlag(tag);
        }
        
        // 
        // Retrieve the type of the string
        //
        tag_t getTagType( std::string tag )
        {
            // Check if the tag is well defined
            if ( tag.empty() )                                          throw "Bad tag";
            if ( tag.size() == 1 && tag[0] == '-' )                     throw "Bad tag";
            if ( tag.size() == 2 && tag[0] == '-' && tag[1] == '-' )    throw "Bag tag";

            // Check tag type
            if ( isFlag( tag ) )    return tag_t::FLAG;
            else                    return tag_t::VALUE;
        }
    }
}

