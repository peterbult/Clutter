// 
// Utils.h
// Clutter
//
// Created by PM Bult on 24-01-2016
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.0
//

#pragma once

namespace Clutter {
    namespace Utils {
        // Define basic tag types
        enum class tag_t { FLAG, VALUE };

        // Support functions
        bool isFlag( std::string tag );
        
        bool isValue( std::string tag );            

        tag_t getTagType( std::string tag );
    }
}

