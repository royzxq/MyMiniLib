//
//  main.cpp
//  Unit_test
//
//  Created by XinquanZhou on 6/8/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include <iostream>
#include "LLTest.h"
#include "gtest/gtest.h"

int main(int argc, char * argv[]) {
    // insert code here...
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
