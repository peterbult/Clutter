// Blocks.h | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#pragma once
#include <vector>
#include <string>

namespace Clutter {
    struct CommandBlock {
        // Internal Alias
        typedef std::string string;

        // Constructor
        CommandBlock()=default;
        CommandBlock( std::vector<string> _values ) : values(_values) { }

        // Property functions
        std::vector<string>::size_type size() { return values.size(); }

        // Data members
        bool            processed = false;  // A state flag

        std::vector<string>  values;             // The list of values
    };

    struct HelpBlock {
        // Internal Alias
        typedef std::string string;

        // Constructor
        HelpBlock( string _tag, string _label, string _help )
            : tag( _tag ), label( _label ), help( _help ) { }

        // Output function
        void print( int tag_size, int label_size );

        // Data members
        string tag;       // The short 'tag' identifier
        string label;     // The long 'label' identifier
        string help;      // The help message
    };
}
