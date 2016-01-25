// 
// Clutter.cpp
// Clutter
//
// Created by PM Bult on 24-01-2016
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.0
//

#include "Clutter.h"
#include "Utils.h"

namespace Clutter {

    // 
    // Constructor
    //
    Clutter::Clutter( int argc, const char* argv[] )
    {
        // Initialize processing variables
        string              flag;
        string              tag;
        std::vector<string> values;

        // Loop over all tags in the command line
        for (int i = 1; i < argc; ++i) {
            // Convert the current entry to a tag
            string flag = string( argv[i] );

            // Ensure the tag is a flag-type
            if ( Utils::isValue( flag ) ) 
                throw "error: parsing error";

            // Ensure the flag does not alread exist
            if ( mCommandMap.count( flag ) > 0 )
                throw "error: duplicate flag";

            // Find the next flag (or the end of list)
            for (i++; i < argc; i++) { 
                // Load the next tag
                tag = string( argv[i] );
                // Test of tag type
                if ( Utils::isFlag( tag ) ) break;                      // flag found: block is complete
                else                        values.push_back( tag );    // value found: add to current block
            }

            // Store the tag & values as a block
            mCommandMap.emplace( flag, CommandBlock(values) );

            // Clear the processing memory
            values.clear();

            // Continue with next block
            // ...
        }

        // Set help flag
        if ( this->has_flag("-h") || this->has_flag("--help") ) {
            mHelpFlag = true;
        }
    }

    //
    // Support function
    // 
    bool Clutter::has_flag( string flag )
    {
        if ( mCommandMap.count( flag ) == 1 )
            return true;
        else
            return false;
    }


    // 
    // Parse termination function
    //
    void Clutter::end_parse()
    {
        // Check the help flag
        if ( mHelpFlag ) {
            printf( "Required arguments:\n" );
            for ( auto& block : mHelpTree_required )
                block.print();

            printf( "Optional arguments:\n" );
            for ( auto& block : mHelpTree_requested )
                block.print();

            exit(0);
        }

        // Check orphan options
        for ( auto& map : mCommandMap ) {
            if ( !map.second.processed ) {
                throw "error: orphan options";
            }
        }
    }
}

