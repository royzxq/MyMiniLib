//
//  Heap-based.h
//  myLib
//
//  Created by XinquanZhou on 3/25/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef myLib_Heap_based_h
#define myLib_Heap_based_h

#include <unordered_set>
#include <iostream>

using namespace std;


class UPNumber {
protected:
    ~UPNumber();
    
public:
    UPNumber();
    UPNumber(int initValue);
    UPNumber(const UPNumber&);
    
    void destroy() {delete this;}
};

class NonNegUPNumber : public UPNumber {
    
    
public:
    NonNegUPNumber();
    ~NonNegUPNumber();
};


class HeapTracked {
    typedef const void * RawAdd;
    static unordered_set<RawAdd> address;
    
public:
    class MissingAddress{};
    HeapTracked();
    virtual ~HeapTracked() = 0;
    static void * operator new(size_t size);
    static void operator delete(void * ptr);
    
    bool isOnHeap() const;
};
void testUPNumber(){
//    UPNumber n;
    UPNumber * p = new UPNumber();
    p->destroy();
    Asset * pn = new Asset;
    delete pn;
    
}

unordered_set<RawAdd> HeapTracked::address;
HeapTracked::~HeapTracked(){}
void * HeapTracked::operator new(size_t size){
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
    const void * ptr = dynamic_cast<const void *> (this); // transfer the pointer to the beginning address of this object so that portable
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
