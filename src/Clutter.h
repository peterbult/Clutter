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
            typedef std::vector vector;

        public:
            bool has_flag( std::string flag );

            template <typename T>
                void require( string tag, string label, T& value, string help );

            template <typename T>
                void request( string tag, string label, T& value, string help );

            void end_parse();
    
        private:
            // Help members
            bool                mHelpFlag = false;
            vector<HelpBlock>   mHelpTree_required;
            vector<HelpBlock>   mHelpTree_requested;

            // Command map
            std::map<string, Block> > mCommandMap;
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
            parse( value, it );

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
            parse( value, it );

            return;
        }
}

