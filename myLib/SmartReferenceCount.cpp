//
//  SmartReferenceCount.cpp
//  myLib
//
//  Created by XinquanZhou on 3/28/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include "SmartReferenceCount.h"



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

