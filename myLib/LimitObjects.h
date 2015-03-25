//
//  LimitObjects.h
//  myLib
//
//  Created by XinquanZhou on 3/24/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__LimitObjects__
#define __myLib__LimitObjects__

#include <stdio.h>
#include <string>
using namespace std;
class PrintJob;

class Printer {
    Printer();
    Printer(const Printer & rhs);
    
public:
    void submitJob(const PrintJob & job);
    void reset();
    void printJob(string & buffer);
    friend Printer& thePrinter();
};


Printer & thePrinter(){
    static Printer p;
    return p;
}


void print(){
    string buffer;
    thePrinter().printJob(buffer);
}

#endif /* defined(__myLib__LimitObjects__) */
