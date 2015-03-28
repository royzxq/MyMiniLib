//
//  SmartReferenceCount.h
//  myLib
//
//  Created by XinquanZhou on 3/28/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//  This is an implementation for reference count base class using smart pointers
//  And the example string class using this technique

#ifndef __myLib__SmartReferenceCount__
#define __myLib__SmartReferenceCount__

#include <stdio.h>
#include <String.h>

template <class T>
class RCPtr { // reference count smart pointer
    T * pointee;
    void init();
public:
    RCPtr(T * dumpPtr = 0);
    RCPtr(const RCPtr & );
    ~RCPtr();
    
    RCPtr & operator = (const RCPtr & );
    T * operator->() const;
    T & operator*() const;
};



class SmartRCObj{ // the reference count base class
public:
    SmartRCObj();
    SmartRCObj(const SmartRCObj &);
    virtual ~SmartRCObj() = 0 ;
    SmartRCObj & operator=(const SmartRCObj&);
    
    void addReference();
    void removeReference();
    
    void makeUnshareable();
    
    bool isShareable() const;
    bool isShared() const;
private:
    size_t refCount;
    bool shareable;
    
};

class SmartString{
public:
    SmartString(const char * value = "");
    // by using smart pointers, we do not need to implement copy constructor and assignment operator
//    SmartString(const SmartString &);
//    SmartString& operator=(const SmartString&);
    const char & operator[](int index) const;
    char & operator[](int index);
    char emptyChar;
private:
    struct SmartStringValue: public SmartRCObj{
        char * data;
        size_t len;
        SmartStringValue(const char * initValue);
        SmartStringValue(const SmartStringValue &);
        void init(const char * initValue);
        
        bool isValidIndex(int index) const;
        ~SmartStringValue();
        
    };
    RCPtr<SmartStringValue> value; // use smart pointer to point reference count objects
};





#endif /* defined(__myLib__SmartReferenceCount__) */









