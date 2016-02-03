// Blocks.cpp | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#include <iostream>

#include "Blocks.h"

namespace Clutter {
    void HelpBlock::print( int tag_size, int label_size )
    {
        std::string format = "  ";
        format += "%-" + std::to_string(tag_size) + "s; ";
        format += "%-" + std::to_string(label_size) + "s | ";
        format += "%s\n";
        printf( format.c_str(), tag.c_str(), label.c_str(), help.c_str() );
    }
}
