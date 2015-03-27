//
//  LimitObjects.h
//  myLib
//
//  Created by XinquanZhou on 3/24/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//  This is an implementation for a base class that can limit the number of instance that can be created, in order to dynamic create and destroy, use should use pointers to create such instance.

#ifndef __myLib__LimitObjects__
#define __myLib__LimitObjects__

#include <stdio.h>
#include "SmartPointers.h"


//template <class BeingCounted>
class Counted {
private:
    static const size_t maxNumObj ; // the max number of objects should be user defined
    static size_t numObj;
    void init();
protected:
    Counted();
    Counted(Counted & );
    virtual ~Counted(){
        --numObj;
    }
public:
    class TooManyObj{}; // the exception class that can be user defined for when the number of obj is over the maximum
    static size_t objCount () {
        return numObj;
    }
    
};

size_t Counted::numObj = 0;


Counted::Counted () {
    init();
}

void Counted::init() {
    if(numObj > maxNumObj) throw TooManyObj();
    ++numObj;
}

// Example to use such base class

class FSA : public Counted{
public:
    static FSA * makeFSA();
    static FSA * makeFSA(const FSA & rhs);
    
private:
    FSA(); // cannot be created directly
    FSA(const FSA& rhs);
};

FSA * FSA::makeFSA(){
    try {
        return new FSA(); // do not have to carry about the limit of obj.

    } catch (TooManyObj & e) {
        // do something;
        throw ;
        return nullptr;
    }
}

FSA * FSA::makeFSA(const FSA &rhs){
    return  new FSA(rhs);
}

const size_t Counted::maxNumObj = 10;

void useFSA(){
    SmartPtr<FSA> pFSA1(FSA::makeFSA());
    SmartPtr<FSA> PFSA2(FSA::makeFSA(*pFSA1));
}







#endif /* defined(__myLib__LimitObjects__) */
