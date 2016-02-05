// Clutter.h | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

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
            typedef std::map<string, CommandBlock>::iterator MapIterator;

        public:
            // Declare public functions
            template <typename T>
                void require( string tag, string label, T& value, string help );

            template <typename T>
                void request( string tag, string label, T& value, string help );

            template <typename T>
                void request( string tag, string label, bool& toggle, T& value, string help );

            void end_parse();
            
            void redial( std::string filename="redial" );

        private:
            // Declare internal functions
            template <typename T>
                void parse( T& value, CommandBlock &block );

            template <typename T>
                void parse( std::vector<T>& value, CommandBlock &block );

            void print_help();

            bool has_flag( std::string flag );
            
            bool help_has_flag( string, string );
            
            MapIterator find_flag( string, string );

        private:
            // Help members
            bool                    mHelpFlag = false;
            std::vector<HelpBlock>  mHelpTree_required;
            std::vector<HelpBlock>  mHelpTree_requested;
            
            // Redial members
            std::string mExecutable;

            // Command map
            std::map<string, CommandBlock> mCommandMap;
    };


    //
    // Template functions
    //
    template <typename T>
        void Clutter::require( string tag, string label, T& value, string help )
        {
            // Safeguard: test require against the help tree
            if ( help_has_flag( tag, label ) )
                throw std::logic_error("logic error: duplicate flag in parse tree: " + tag + "/" + label);
            
            // Store the require in the help tree
            mHelpTree_required.emplace_back( tag, label, help );
            
            // Check for help request
            if ( mHelpFlag ) return;
            
            // Find the flag position in the Command Map
            auto it = this->find_flag( tag, label );
            
            // Test if the flag is found
            if ( it == mCommandMap.end() )
                throw std::runtime_error("parse error: required flag is missing: " + tag + "/" + label);
                
            // Process the flag
            try {
                parse( value, (it->second) );
            }
            catch( const std::exception& e ) {
                throw std::runtime_error("parse error: could not parse: " + tag + "/" + label + ": " + e.what() );
            }

            return;
        }

    template <typename T>
        void Clutter::request( string tag, string label, T& value, string help )
        {
            // Safeguard: test require against the help tree
            if ( help_has_flag( tag, label ) )
                throw std::logic_error("logic error: duplicate flag in parse tree: " + tag + "/" + label);
            
            // Store the require in the help tree
            mHelpTree_requested.emplace_back( tag, label, help );

            // Check for help request
            if ( mHelpFlag ) return;
            
            // Find the flag position in the Command Map
            auto it = this->find_flag( tag, label );

            // Test if the flag is found
            if ( it == mCommandMap.end() )
                return;

            // Process the flag
            try {
                parse( value, (it->second) );
            }
            catch( const std::exception& e ) {
                throw std::runtime_error("parse error: could not parse: " + tag + "/" + label + ": " + e.what() );
            }

            return;
        }

    template <typename T>
        void Clutter::request( string tag, string label, bool& toggle, T& value, string help )
        {
            // Safeguard: test require against the help tree
            if ( help_has_flag( tag, label ) )
                throw std::logic_error("logic error: duplicate flag in parse tree");
            
            // Store the require in the help tree
            mHelpTree_requested.emplace_back( tag, label, help );

            // Check for help request
            if ( mHelpFlag ) return;

            // Find the flag position in the Command Map
            auto it = this->find_flag( tag, label );

            // Test if the flag is found
            if ( it == mCommandMap.end() )
                return;

            // If found: toggle the boolian
            toggle = !toggle;

            try {
                if (it->second.size() > 0) 
                    // If there is an argument in the block: parse to value
                    parse( value, (it->second) );
                else
                    // Manually set processed flagelse 
                    it->second.processed = true;
            }
            catch( const std::exception& e ) {
                throw std::runtime_error("parse error: could not parse: " + tag + "/" + label + ": " + e.what() );
            }

            return;
        }

    template <typename T>
        void Clutter::parse( T& value, CommandBlock& block )
        {
            // Test block size
            if ( block.size() == 0 )
                throw std::runtime_error("flag argument missing");
            if ( block.size() > 1 )
                throw std::runtime_error("orphan argument: " + block.values[1] );

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
                throw std::runtime_error("flag argument missing");

            // Convert string to template type
            for ( auto& e : block.values ) {
                value.push_back( fromString<T>( e ) );
            }

            // Mark as processed
            block.processed = true;
        }

    // Forward declare other specializations
    template <> void Clutter::parse<bool>( bool& value, CommandBlock& block );
    template <> void Clutter::parse<std::string>( std::string& value, CommandBlock& block );
}
