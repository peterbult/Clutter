//
// Clutter.h
// Clutter
//
// Created by PM Bult on 24-01-2016
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.0
//

#pragma once
#include <vector>
#include <map>

#include <CustomTools/Convert.h>

#include "Blocks.h"

namespace Clutter {

    //
    // Clutter command line parser class
    //
    class Clutter {
        public:
            Clutter( int argc, const char* argv[] );
            virtual ~Clutter() { }

        private:
            // Define internal aliases
            typedef std::string string;

        public:
            // Declare public functions
            template <typename T>
                void require( string tag, string label, T& value, string help );

            template <typename T>
                void request( string tag, string label, T& value, string help );

            template <typename T>
                void request( string tag, string label, bool& toggle, T& value, string help );

            void end_parse();

        private:
            // Declare internal functions
            template <typename T>
                void parse( T& value, CommandBlock &block );

            template <typename T>
                void parse( std::vector<T>& value, CommandBlock &block );

            void print_help();

            bool has_flag( std::string flag );

        private:
            // Help members
            bool                    mHelpFlag = false;
            std::vector<HelpBlock>  mHelpTree_required;
            std::vector<HelpBlock>  mHelpTree_requested;

            // Command map
            std::map<string, CommandBlock> mCommandMap;
    };


    //
    // Template functions
    //
    template <typename T>
        void Clutter::require( string tag, string label, T& value, string help )
        {
            // Store the require in the help tree
            mHelpTree_required.emplace_back( tag, label, help );

            // Check for help request
            if ( mHelpFlag ) return;

            // Check if short-format flag is present
            auto it = mCommandMap.find( tag );

            // If not: check if if the long-format flag is present
            if ( it == mCommandMap.end() )
                it = mCommandMap.find( label );

            // If not: throw a parse failure
            if ( it == mCommandMap.end() )
                throw "error: parse failure: required option not found";

            // If found: parse the values
            std::cerr << "Parse " << tag << " or " << label << std::endl;
            parse( value, (it->second) );

            return;
        }

    template <typename T>
        void Clutter::request( string tag, string label, T& value, string help )
        {
            // Store the require in the help tree
            mHelpTree_requested.emplace_back( tag, label, help );

            // Check for help request
            if ( mHelpFlag ) return;

            // Check if short-format flag is present
            auto it = mCommandMap.find( tag );

            // If not: check if if the long-format flag is present
            if ( it == mCommandMap.end() )
                it = mCommandMap.find( label );

            // If not: terminate the parse
            if ( it == mCommandMap.end() )
                return;

            // If found: parse the values
            parse( value, (it->second) );

            return;
        }

    template <typename T>
        void Clutter::request( string tag, string label, bool& toggle, T& value, string help )
        {
            // Store the require in the help tree
            mHelpTree_requested.emplace_back( tag, label, help );

            // Check for help request
            if ( mHelpFlag ) return;

            // Check if short-format flag is present
            auto it = mCommandMap.find( tag );

            // If not: check if if the long-format flag is present
            if ( it == mCommandMap.end() )
                it = mCommandMap.find( label );

            // If not: terminate the parse
            if ( it == mCommandMap.end() )
                return;

            // If found: toggle the boolian
            toggle = !toggle;

            // If there is an argument in the block: parse to value
            if (it->second.size() > 0) {
                parse( value, (it->second) );
            }
            else { // Manually set processed flag
                it->second.processed = true;
            }

            return;
        }

    template <typename T>
        void Clutter::parse( T& value, CommandBlock& block )
        {
            // Test block size
            if ( block.size() == 0 )
                throw "error: flag option is missing";
            if ( block.size() > 1 )
                printf( "warning: orhpan value\n" );

            // Convert string to template type
            // value = fromString<T>( block.values[0] );
            value = sto<T>( block.values[0] );

            // Mark block as processed
            block.processed = true;
        }

    // Vector specialization
    template <typename T>
        void Clutter::parse( std::vector<T>& value, CommandBlock& block )
        {
            // Clear the values
            value.clear();
            
            // Test block size
            if ( block.size() == 0 )
                throw "error: flag options are missing";

            // Convert string to template type
            for ( auto& e : block.values ) {
                value.push_back( fromString<T>( e ) );
            }

            // Mark as processed
            block.processed = true;
        }

    // Forward declare other specializations
    template <> void Clutter::parse<bool>( bool& value, CommandBlock& block );
}
