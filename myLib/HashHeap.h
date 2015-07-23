//
//  HashHeap.h
//  myLib
//
//  Created by XinquanZhou on 7/23/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef myLib_HashHeap_h
#define myLib_HashHeap_h

#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
#include"MyExceptions.h"



template <class T>
class HashHeap {
    std::vector<T> heap;
    int size_t;
    std::string mode;

    class Node {
    public:
        int idx;
        int num;
        Node(const Node& now){
            idx = now.idx;
            num = now.num;
        }
        
        Node(int first, T second):idx(first),num(second){
        }
    };
    
    std::unordered_map<T,Node> hash;
    
    int parent(int idx){
        if (idx == 0) {
            return -1;
        }
        else{
            return (idx - 1)/2;
        }
    }
    
    int lson(int idx){
        try {
            int res = idx * 2 + 1;
            if (res < heap.size()) {
                return res;
            }
            else{
                throw BeyondBoundry();
            }
        } catch (BeyondBoundry & e) {
            throw;
        }
    }
    
    int rson(int idx){
        try {
            int res = idx * 2 + 2;
            if (res < heap.size()) {
                return res;
            }
            else{
                throw BeyondBoundry();
            }
        } catch (BeyondBoundry & e) {
            throw;
        }
    }
    
    bool compare(T a, T b);
    void swap(int idA, int idB);
    
    void siftup(int idx){
        while (parent(idx) > -1) {
            int parentId = parent(idx);
            if(compare(heap[parentId],heap[idx])){
                break;
            }else{
                swap(idx, parentId);
            }
            id = parentId;
        }
    }
    void siftdown(int idx){
        while (lson(idx) < heap.size()) {
            int leftid = lson(idx);
            int rightid = rson(idx);
            int son;
            if(rightid >= heap.size() || (compare(heap[leftid], heap[rightid]))){
                son = leftid;
            } else{
                son = rightid;
            }
           if(compare(heap[idx],heap[son])){
               break;
           }
           else{
               swap(idx,son);
           }
           idx = son;
        }
    }
public:
    
    // API
    HashHeap(std::string mod):size_t(0),mode(mod){
    }
    
    T peak() const;
    int size() const{
        return size_t;
    }
    bool empty() const{
        return heap.size() == 0;
    }
    T poll() ;
    void add(T now);
    void erase(T now);
};


template <class T>
T HashHeap<T>::peak() const {
    try {
        if (heap.size() > 0) {
            return heap.front();
        }
        else{
            throw BeyondBoundry();
        }
    } catch (BeyondBoundry & e) {
        throw;
    }
    
}



template <class T>
bool HashHeap<T>::compare(T a, T b) {
    if(a <= b){
        if (mode == "min") {
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (mode == "min") {
            return false;
        }
        else{
            return true;
        }
    }
}

template <class T>
void HashHeap<T>::swap(int idA, int idB) {
    T valA = heap[idA];
    T valB = heap[idB];
    
    int numA = hash[valA].num;
    int numB = hash[valB].num;
    hash[valB] = Node(idA, numB);
    hash[valA] = Node(idB, numA);
    
    heap[idA] = valB;
    heap[idB] = valA;
}

template <class T>
T HashHeap<T>::poll() {
    size_t --;
    T now = heap.front();
    Node hashnow = hash[now];
    if (hashnow.num == 1) {
        swap(0,heap.size()-1);
        hash.erase(now);
        heap.pop_back();
        if(heap.size()>0){
            siftdown(0);
        }
    }else{
        hash[now] = Node(0, hashnow.num - 1);
    }
    return now;
}

template <class T>
void HashHeap<T>::add(T now) {
    size_t ++;
    if (hash.find(now) != hash.end()) {
        hash[now].num ++;
    }
    else{
        heap.push_back(now);
        hash[now] = Node(heap.size()-1,1));
    }
    siftdown(heap.size()-1);
}

template <class T>
void HashHeap<T>::erase(T now) {
    if(hash.find(now) == hash.end()) return;
    size_t --;
    Node hashnow = hash[now];
    int idx = hashnow.idx;
    int num = hashnow.num;
    if(num == 1){
        swap(idx,heap.size()-1);
        hash.erase(now);
        heap.pop_back();
        if(heap.size() > idx){
            siftup(idx);
            siftdown(idx);
        }
    }
    else{
        hash[now].num --;
    }
}


#endif
