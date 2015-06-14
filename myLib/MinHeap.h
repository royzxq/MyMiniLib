//
//  MinHeap.h
//  myLib
//
//  Created by XinquanZhou on 6/14/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__MinHeap__
#define __myLib__MinHeap__

#include <stdio.h>
#include <vector>
#include <utility>

template <class T>
class MinHeap {
    std::vector<T> _vector;
    int _getParentIdx(int index) const;
    int _getLeftIdx(int index) const;
    int _getRightIdx(int) const;
    int _size;
    void _bubbleUp(int index);
    void _bubleDown(int index);
    void _heapify();
public:
    MinHeap():_size(0){}
    MinHeap(const std::vector<T> & Vec);
    void Insert(T Val);
    void DecreaseKey(T val, int index);
    T DeleteMin();
    T GetMin() const;
    int Size() const;
};

template <class T>
MinHeap<T>::MinHeap(const std::vector<T> & Vec):_vector(Vec){
    _size = Vec.size();
    _heapify();
}

// the input of output index are all zero-based
template <class T>
int MinHeap<T>::_getParentIdx(int index) const {
    if (index <= 0) {
        return -1;
    }
    return  static_cast<int>((index+1) / 2 - 1);
}

template <class T>
int MinHeap<T>::_getLeftIdx(int index) const {
    int idx = (index+1) * 2 - 1;
    if (idx >= _size) {
        return -1;
    }
    return idx;
}

template <class T>
int MinHeap<T>::_getRightIdx(int index) const {
    int idx = (index + 1) * 2;
    if(idx >= _size){
        return -1;
    }
    return idx;
}

template <class T>
void MinHeap<T>::_heapify() {
    for (int i = _size ; i >= 0; i--) {
        _bubleDown(i);
    }
}
template <class T>
void MinHeap<T>::_bubbleUp(int curIdx) {
    int parIdx = _getParentIdx(curIdx);
    while ( parIdx != -1) {
        if (_vector[curIdx] < _vector[parIdx]) {
            std::swap(_vector[curIdx], _vector[parIdx]);
            curIdx = parIdx;
            parIdx = _getParentIdx(parIdx);
        }
        else{
            break;
        }
    }
}

template <class T>
void MinHeap<T>::_bubleDown(int index) {
    int left = _getLeftIdx(index);
    if (left == -1) {
        return;
    }
    int right = _getRightIdx(index);
    int minIdx = index;
    if (_vector[index] > _vector[left]) {
        minIdx = left;
    }
    if (right != -1 && _vector[minIdx] > _vector[right]) {
        minIdx = right;
    }
    if (minIdx != index) {
        std::swap(_vector[index], _vector[minIdx]);
        _bubleDown(minIdx);
    }
}
template <class T>
int MinHeap<T>::Size() const {
    return _size;
}

template <class T>
void MinHeap<T>::Insert(T Val) {
    _vector.push_back(Val);
    _size ++;
    int curIdx = _size-1;
    _bubbleUp(curIdx);
}


template <class T>
void MinHeap<T>::DecreaseKey(T val, int index) {
    try {
        if (index < 0 || index >= _size ) {
            throw ;
        }
        _bubbleUp(index);
        
    } catch (std::exception & e) {
        throw ;
    }
}

template <class T>
T MinHeap<T>::GetMin() const{
    return _vector[0];
}

template <class T>
T MinHeap<T>::DeleteMin() {
    T min = _vector[0];
    std::swap(_vector[0], _vector[_size-1]);
    _vector.pop_back();
    _size --;
    _bubleDown(0);
    return min;
}
#endif /* defined(__myLib__MinHeap__) */
