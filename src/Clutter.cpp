// Clutter.cpp | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#include <algorithm>

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
        string              argument;
        std::vector<string> values;

        // Loop over all arguments in the command line
        // ~> Skip the executable name
        for (int i = 1; i < argc; ++i) {
            // Convert the current argument to a flag
            string flag = string( argv[i] );

            // Ensure the argument is indeed flag-type
            if ( Utils::isValue( flag ) )
                throw "error: parsing error";

            // Ensure the flag does not alread exist
            if ( mCommandMap.count( flag ) > 0 )
                throw "error: duplicate flag";

            // Find the next flag (or the end of list)
            for (i++; i < argc; i++) {
                // Load the next argument
                argument = string( argv[i] );
                // Test the argument type
                if ( Utils::isFlag( argument ) ) { i--; break; }    // flag found: block is complete
                else values.push_back( argument );                  // value found: add to current block
            }

            // Store the flag & values as a CommandBlock
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
    // Parse templace specializations
    //
    // -> Boolian specialization
    template <>
        void Clutter::parse( bool& value, CommandBlock &block )
        {
            // Test block size
            if ( block.size() > 0 )
                printf( "warning: orhpan value\n" );

            // Flip value
            value = !value;

            // Mark as processed
            block.processed = true;
        }

    // -> String specialization
    template <>
        void Clutter::parse( string& value, CommandBlock &block )
        {
            // Test block size
            if ( block.size() == 0 )
                throw "error: flag option is missing";
            if ( block.size() > 1 )
                printf( "warning: orhpan value\n" );

            // Flip value
            value = block.values[0];

            // Mark as processed
            block.processed = true;
        }

    //
    // Parse termination function
    //
    void Clutter::end_parse()
    {
        // Check the help flag
        if ( mHelpFlag ) {
            // Print the help table
            print_help();

            // Terminate program
            exit(0);
        }

        // Check orphan options
        for ( auto& map : mCommandMap ) {
            if ( !map.second.processed ) {
                throw "error: orphan options";
            }
        }
    }
    
    //
    // Redial function: store parameters to file
    //
    void Clutter::redial( std::string name )
    {
        // Create the redial file
        FILE *os = fopen( "redial", "w" );
        
        // Set the program name
        fprintf( os, "./%s ", name.c_str() );
        
        // Print the command map
        for ( auto& map : mCommandMap ) {
            // Print the key
            fprintf( os, "%s ", map.first.c_str() );
            // Print the values
            for ( auto& v : map.second.values ) 
                 fprintf( os, "%s ", v.c_str() ); 
        }
        // End the command line
        fprintf( os, "\n" );
        
        // Close the file stream
        fclose(os);
    }

    //
    // Print help table
    //
    void Clutter::print_help()
    {
        // Resolve label width
        unsigned long max_width = 0;

        // Search the required tree
        for ( auto& block : mHelpTree_required )
             max_width = std::max( max_width, block.label.size() );

        // Search the requested tree
        for ( auto& block : mHelpTree_requested )
             max_width = std::max( max_width, block.label.size() );

        // Add two characters
        max_width = std::max( (unsigned long)(16), max_width+2 );

        // Print the help table
        printf( "Required arguments:\n" );
        for ( auto& block : mHelpTree_required )
            block.print( 6, max_width );

        printf( "Optional arguments:\n" );
        for ( auto& block : mHelpTree_requested )
            block.print( 6, max_width );
    }
}
