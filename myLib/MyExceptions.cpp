//
//  MyExceptions.cpp
//  myLib
//
//  Created by XinquanZhou on 7/2/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include "MyExceptions.h"

const char * BeyondBoundry::what() const throw(){
    return "The parameters is out of boundry";
}

const char * FailInit::what() const throw(){
    return "Something wrong when you initialize objects";
}

const char * InvalidParams::what() const throw(){
    return "The parameters are not allowed";
}

const char * NoValidOp::what() const throw(){
    return "There is no valid operation";
}