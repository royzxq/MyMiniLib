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
//using namespace std;

class PrintJob;

namespace PrintingStuff {
    class Printer {
        Printer();
        Printer(const Printer & rhs);
        
    public:
        static Printer & thePrinter();
        void submitJob(const PrintJob & job);
        void reset();
        void printJob(std::string & buffer);
        friend Printer& thePrinter();
    };
    
    
    Printer & Printer::thePrinter(){
        static Printer p;
        return p;
    }
    
    class MultiPrinter{
    public:
        MultiPrinter();
        ~MultiPrinter();
    private:
        static size_t numObj;
        MultiPrinter(const MultiPrinter & rhs);
    };
    
    size_t MultiPrinter::numObj = 0;
    MultiPrinter::MultiPrinter(){
        if(numObj > 1){
            throw ;
        }
        ++numObj;
    }
    MultiPrinter::~MultiPrinter(){
        --numObj;
    }
    
    class FSA{
    public:
        static FSA * makeFSA();
        static FSA * makeFSA(const FSA & rhs);
        
    private:
        static size_t numObj;
        FSA();
        FSA(const FSA& rhs);
    };
    
    void TestFSA(){
        std::auto_ptr<FSA> pfsa1(FSA::makeFSA());
        std::auto_ptr<FSA> pfsa2(FSA::makeFSA(*pfsa1));
    }
    
    size_t FSA::numObj = 0;
    FSA* FSA::makeFSA(){
        if (numObj > 1) {
            throw ;
        }
        ++ numObj ;
        return new FSA();
    }
    FSA* FSA::makeFSA(const PrintingStuff::FSA &rhs){
        return new FSA(rhs);
    }
    
    class DynamicMultiPrinter{
    public:
        static DynamicMultiPrinter * makePrinter();
        static DynamicMultiPrinter * makePrinter(const DynamicMultiPrinter &);
    private:
        static size_t numObj;
        static const size_t maxNumObj = 10;
        DynamicMultiPrinter();
        ~DynamicMultiPrinter();
    };
    size_t DynamicMultiPrinter::numObj = 0;
    DynamicMultiPrinter * DynamicMultiPrinter::makePrinter(){
        if (numObj > maxNumObj) {
            return nullptr;
        }
        return new DynamicMultiPrinter();
    }
    DynamicMultiPrinter::DynamicMultiPrinter(){
        if(numObj > maxNumObj){
            throw ;
        }
        ++numObj;
    }
    
}










#endif /* defined(__myLib__LimitObjects__) */
