//
//  ReferenceCount.h
//  myLib
//
//  Created by XinquanZhou on 3/27/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//  this is an implementation for a reference count abstract base class
//  and an example of using it to create a simple reference count string class

#ifndef __myLib__ReferenceCount__
#define __myLib__ReferenceCount__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class RCObj {
    size_t refCount;
    bool shareable;
    
public:
    RCObj();
    RCObj(const RCObj & rhs);
    RCObj& operator=(const RCObj & rhs);
    virtual ~RCObj() = 0;
    
    void addReference();
    void removeReference();
    void markUnShareable();
    bool isShareable() const;
    
    bool isShared() const;
};


RCObj::RCObj():refCount(0),shareable(true){}

RCObj::RCObj(const RCObj & ):refCount(0),shareable(true){}


RCObj& RCObj::operator=(const RCObj &){
    return *this;
}

RCObj::~RCObj(){}

void RCObj::addReference(){
    ++refCount;
}

void RCObj::removeReference(){
    if (--refCount == 0 ) {
        delete this;
    }
}

void RCObj::markUnShareable(){
    shareable = false;
}

bool RCObj::isShareable() const{
    return shareable;
}

bool RCObj::isShared() const{
    return refCount > 1;
    
}

class String {
    //    char * data;
    
//    struct StringValue{
//        size_t refCount;
//        size_t len;
//        char * data;
//        bool shareable;
//        StringValue(const char * rhs);
//        ~StringValue();
//    };
    struct StringValue: public RCObj{
        char * data;
        size_t len;
        StringValue(const char * initValue);
        ~StringValue();
    };

    StringValue * value;
    char emptyChar;
public:
    String(const char * value = "");
    String(const String& rhs);
    String& operator=(const String& rhs);
    ~String();
    const char& operator[] (int index) const;
    char& operator[](int index) ;
    bool isValidIndex(int index) const;
};

String::StringValue::StringValue(const char * rhs) {
    data = new char[strlen(rhs)+1];
    len = strlen(rhs);
    strcpy(data, rhs);
}

String::StringValue::~StringValue(){
    delete []data;
}

String::String(const char * value):value(new StringValue(value)){
}

String::String(const String& rhs){
    if (rhs.value->isShareable()) {
        value = rhs.value;
//        ++value -> refCount;
        value -> addReference();
    }
    else{
        value = new StringValue(rhs.value->data);
    }
}

String::~String(){
//    if (--value->refCount == 0) {
//        delete value;
//    }
    value -> removeReference();
}

bool String::isValidIndex(int index) const{
    if (index <= value -> len && index >= 0) {
        return true;
    }
    else return false;
}
String& String::operator=(const String &rhs){
    if (this == &rhs) {
        return *this;
    }
    
    value -> removeReference();
    
    value = rhs.value;
    value -> addReference();
    return *this;
}

const char & String::operator[](int index) const{
    if (isValidIndex(index)) {
        return value -> data[index];
    }
    else return emptyChar;
}

char & String::operator[](int index){
    if (isValidIndex(index)) {
        if (value->isShared()) {
            value -> removeReference();
            value = new StringValue(value->data);
        }
        value -> markUnShareable();
        return value->data[index];
    }
    else return emptyChar;
}


#endif /* defined(__myLib__ReferenceCount__) */
