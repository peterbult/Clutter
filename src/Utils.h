// Utils.h | Created on 24-01-2016
//
// Copyright (c) 2016 P.M. Bult
// This work is provided under the MIT license

#pragma once
#include <string>

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
