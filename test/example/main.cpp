// example/main.cpp | Created on 23-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#include <iostream>
#include <thread>
#include <chrono>

#include "Clutter.h"

// Define a settings container
struct Settings {
    // Define mandatory input
    std::string filename;
    long        runtime;

    // Define optional input
    std::vector<std::string> search_paths;

    double      custom_pi   = 3.14159265359;
    bool        verbose     = false;

    // Define option-with-value
    bool        useConfig   = false;
    std::string configPath  = "default.conf";
};

// Forward declarations
void core_program( Settings& args );

// Main interface
int main(int argc, const char *argv[])
{
    try
    {
        // Initialize a settings container
        Settings args;

        // Initialize the command line parser
        Clutter::Clutter cl( argc, argv );

        // Define the parsing tree
        //
        // ~~> Mandatory user input:
        //
        cl.require( "-f", "--file", args.filename,      "Enter filename" );
        cl.require( "",   "--run",  args.runtime,       "Enter program runtime [ms]" );
        //
        // ~~> Optional user input:
        //
        cl.request( "-s", "--paths",   args.search_paths,   "Give search paths" );
        cl.request( "",   "--custom",  args.custom_pi,      "Give your value of pi" );
        cl.request( "-v", "--verbose", args.verbose,        "Enable verbose mode" );
        //
        // ~~> Option-with-value user input:
        //
        cl.request( "", "--config", args.useConfig, args.configPath, "Enable custom config [default.conf]");

        // Finalize the parsing tree
        cl.end_parse();

        // Run the core program
        core_program( args );
    }
    catch (const char* e )
    {
        std::cout << e << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

// Core program implementation
void core_program( Settings& args )
{
    // Print a header
    std::cout << std::boolalpha << std::endl;
    std::cout << " A test program!" <<std::endl;
    std::cout << std::endl;

    // Pseudo-read file
    std::cout << " > Reading input file [ " << args.filename << " ]" << std::endl;

    // Loading custom config
    std::cout << " > Use custom config: " << args.useConfig << std::endl;
    if ( args.useConfig ) {
        std::cout << " > Loading config [ " << args.configPath << " ]" << std::endl;
    }

    // Wait for runtime
    for ( auto &path : args.search_paths ) {
        std::cout << " > Searching [ " << path << " ] for file" << std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds( args.runtime ));
    }
    std::cout << std::endl;

    // Dump settings:
    std::cout << " > Settings: " << std::endl;
    std::cout << " x verbose: " << args.verbose << std::endl;
    std::cout << " x pi.....: " << args.custom_pi << std::endl;
    std::cout << std::endl;
}
