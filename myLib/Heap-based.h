//
//  Heap-based.h
//  myLib
//
//  Created by XinquanZhou on 3/25/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//  This is a implementation for an abstract class which can track the current obj is on the heap, user defined class can simply inherite this one to obtain the ablity of "heap tracker"; and another class that cannot be on the heap 

#ifndef myLib_Heap_based_h
#define myLib_Heap_based_h

#include <unordered_set>
//#include <iostream>

using namespace std;

class HeapTracked { // the base class that can track the current obj is on the heap or not
    typedef const void * RawAdd;
    static unordered_set<RawAdd> address; // use hash table to store the global address
    
public:
    class MissingAddress{}; // The exception class that use can define
    HeapTracked();
    virtual ~HeapTracked() = 0; // this is an abstract class
    static void * operator new(size_t size); // overload operator new and delete to track the address created on the heap
    static void operator delete(void * ptr);
    
    bool isOnHeap() const; // return whether on the heap
};

unordered_set<RawAdd> HeapTracked::address; // init the static member

HeapTracked::~HeapTracked(){}

void * HeapTracked::operator new(size_t size){ // in addition to normal operator new, add new address to cache
    void * memPtr = ::operator new(size);
    address.insert(memPtr);
    return memPtr;
}

void HeapTracked::operator delete(void * ptr){
    if (!ptr) {
        return;
    }
    if (address.find(ptr) != address.end()) {
        address.erase(ptr);
        ::delete(ptr);
    }
    else{
        throw MissingAddress();
    }
    
}
bool HeapTracked::isOnHeap() const{
    const void * ptr = dynamic_cast<const void *> (this); // transfer the pointer to the beginning address of this object so that be portable
    if (address.find(ptr) != address.end()) {
        return true;
    }
    else{
        return false;
    }
}



namespace Prohibit_Heap {
    class nonHeapUPNumber{ // class that cannot be init directly by new
    private:
        static void * operator new(size_t size);
        static void operator delete(void * ptr);
        static void * operator new[](size_t size);
        static void operator delete[](void * ptr);
        
    };    
    class deriveNonHeapNumber : public nonHeapUPNumber{ // also cannot be init directly by new
    };
    
    class Asset{ // can be init by new although it contain nonHeapUPNumber member
    public:
        Asset(int initValue);
    private:
        nonHeapUPNumber value;
    }
    
    
}




#endif
