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



template <class T>
void RCPtr<T>::init() {
    if (pointee == 0) {
        return;
    }
    if (!pointee->isShareable()) {
        pointee = new T(*pointee);
    }
    pointee -> addReference();
}

template <class T>
RCPtr<T>::RCPtr (T * dumpPtr):pointee(dumpPtr){
    init();
}

template <class T>
RCPtr<T>::RCPtr (const RCPtr& rhs):pointee(rhs.pointee){
    init();
}

template <class T>
RCPtr<T>::~RCPtr (){
    if (pointee) {
        pointee -> removeReference();
    }
}

template <class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs) {
    if (pointee == rhs.pointee) {
        return *this;
    }
    else{
        T * oldPointee = pointee;
        pointee = rhs.pointee;
        init();
        if (oldPointee) {
            oldPointee->removeReference();
        }
        return *this;
    }
}

template <class T>
T * RCPtr<T>::operator->()const {
    return pointee;
}

template <class T>
T & RCPtr<T>::operator*()const {
    return *pointee;
}




SmartRCObj::SmartRCObj():refCount(0),shareable(true){}

SmartRCObj::SmartRCObj(const SmartRCObj &):refCount(0),shareable(true){
}

SmartRCObj& SmartRCObj::operator=(const SmartRCObj &){
    return *this;
}

SmartRCObj::~SmartRCObj(){}

void SmartRCObj::addReference(){
    ++refCount;
}
void SmartRCObj::removeReference(){
    if (--refCount == 0) {
        delete this;
    }
}

void SmartRCObj::makeUnshareable(){
    shareable = false;
}

bool SmartRCObj::isShareable() const{
    return shareable;
}

bool SmartRCObj::isShared() const{
    return refCount > 1;
}

void SmartString::SmartStringValue::init(const char * initValue){
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
    len = strlen(initValue);
}

SmartString::SmartStringValue::SmartStringValue(const char * initValue){
    init(initValue);
}

SmartString::SmartStringValue::SmartStringValue(const SmartStringValue & rhs){
    init(rhs.data);
}

SmartString::SmartStringValue::~SmartStringValue(){
    delete [] data;
}

bool SmartString::SmartStringValue::isValidIndex(int index) const{
    if (index <= len && index >= 0) {
        return true;
    }
    return false;
}

SmartString::SmartString(const char * initValue):value(new SmartStringValue(initValue)){}



const char& SmartString::operator[](int index) const{
    if (value->isValidIndex(index)) {
        return value->data[index];
    }
    return emptyChar;
}

char & SmartString::operator[](int index){
    if (!value->isValidIndex(index)) {
        return emptyChar;
    }
    if (value->isShared()) {
        value = new SmartStringValue(value->data);
    }
    value -> makeUnshareable();
    return value->data[index];
}




#endif /* defined(__myLib__SmartReferenceCount__) */









