//
//  SmartPointers.h
//  myLib
//
//  Created by XinquanZhou on 3/26/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__SmartPointers__
#define __myLib__SmartPointers__

#include <stdio.h>
#include <string>

namespace SmartPointer {
    template <class T>
    class auto_ptr {
        T * pointee;
        
    public:
        auto_ptr(auto_ptr<T> & rhs);
        auto_ptr<T> & operator=(auto_ptr<T> & rhs);
    };
    
    template <class T>
    auto_ptr<T>::auto_ptr (auto_ptr<T> & rhs) {
        pointee = rhs.pointee;
        rhs.pointee = 0;
    }
    
    template <class T>
    auto_ptr<T> & auto_ptr<T>::operator=(auto_ptr<T> & rhs) {
        if (this == & rhs) {
            return this;
        }
        delete pointee;
        pointee = rhs.pointee;
        rhs.pointee = 0;
        return *this;
    }
    
    template <class T>
    class SmartPtr {
        T * pointee;
        
    public:
        SmartPtr(T * ptr = 0) ;
        SmartPtr(const SmartPtr & rhs);
        
        SmartPtr<T> & operator =(const SmartPtr & rhs);
        T* operator -> () const;
        T& operator &() const;
        bool operator!() const;
        
        template <class NewType>
        operator SmartPtr<NewType>(){
            return SmartPtr<NewType> (pointee);
        }
        //    operator T * () {return  pointee;}
    };
    
    template <class T>
    T *  SmartPtr<T>::operator-> () const {
        return pointee;
    }
    
    template <class T>
    T &  SmartPtr<T>::operator&() const {
        return *pointee;
    }
    
    template <class T>
    bool SmartPtr<T>::operator!() const {
        return pointee == 0;
    }


}

class MusicProduct {
    
    
public:
    MusicProduct(const std::string & title);
    virtual void play() const = 0 ;
    virtual void displayTitle() const = 0 ;
    
};

class Cassette: public MusicProduct {
public:
    Cassette(const std::string & title);
    virtual void play() const;
    virtual void displayTitle() const;
};

class CD : public MusicProduct {
    
    
public:
    CD(const std::string & title);
    virtual void play() const;
    virtual void displayTitle() const;
};

void displayAndPlay(const MusicProduct * pmp, int numTimes){
    for (int i = 0 ; i < numTimes; i++) {
        pmp -> displayTitle();
        pmp -> play();
    }
}


//void displayAndPlay(const SmartPtr<MusicProduct > & pmp, int howMany){
//};
//

template <class T>
class SmartPtr {
public:
    explicit SmartPtr(T * p = 0 );
    
    template<class NewType>
    SmartPtr(SmartPtr<NewType> & rhs);  // template copy constructor for converting derived-like type
    
    ~SmartPtr();
    
    template<class NewType>
    SmartPtr<T> & operator = (SmartPtr<NewType> & rhs); // overload = operator
    
    T & operator * () const;
    T * operator -> () const;
    
    T * get() const; // get the current dump pointer within the object
    T * release();
    
    void reset(T * p = 0 ); // delete the current dump pointer and have a new one
    template<class NewType>
    friend class SmartPtr<NewType>;
private:
    T * pointee;
};
template <class T>
inline SmartPtr<T>::SmartPtr(T * p ): pointee(p) {
}

template <class T>
template <class NewType>
inline SmartPtr<T>::SmartPtr(SmartPtr<NewType> & rhs):pointee(rhs.release()) {
}

template <class T>
inline SmartPtr<T>::~SmartPtr() {
    delete pointee;
}

template <class T>
template <class NewType>
inline SmartPtr<T> & SmartPtr<T>::operator=(SmartPtr<NewType> &rhs) {
    if (this != &rhs) {
        reset(rhs.release()); // transfer the ownership from rhs to this
    }
    return *this;
}

template <class T>
inline T& SmartPtr<T>::operator*() const {
    return * pointee;
}
template <class T>
inline T* SmartPtr<T>::operator->() const {
    return  pointee;
}

template <class T>
inline T* SmartPtr<T>::get() const{
    return pointee;
}

template <class T>
inline T* SmartPtr<T>::release() {
    T * oldPointee = pointee;
    pointee = 0 ;
    return oldPointee;
}

template <class T>
inline void SmartPtr<T>::reset(T * p){
    if (pointee != p) {
        delete pointee;
        pointee = p;
    }
    
}








#endif /* defined(__myLib__SmartPointers__) */
