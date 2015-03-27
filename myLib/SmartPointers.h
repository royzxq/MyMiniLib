//
//  SmartPointers.h
//  myLib
//
//  Created by XinquanZhou on 3/26/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__SmartPointers__
#define __myLib__SmartPointers__
/*
  A simple smart pointer implementation: 
 usage: Generally the same as "dump" pointer but don't have to delete manually. Declare it as SmartPtr<T> sPtr = new T ();
 Notion: There is no const pointer within SmartPtr class, therefore it cannot emulate const pointers. 
 */

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
//template<class NewType> friend class SmartPtr<NewType>;
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
