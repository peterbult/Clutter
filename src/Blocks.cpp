// 
// Blocks.cpp
// Clutter
//
// Created by PM Bult on 24-01-2016
// Copyright (c) P.M. Bult. All rights reserved.
//
// Version 1.0
//

#include <iostream>

#include "Blocks.h"

namespace Clutter {
    void HelpBlock::print()
    {
        printf( "%s %s %s\n", mTag, mLabel, mHelp );
    }
}

