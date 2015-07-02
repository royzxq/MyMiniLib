//
//  SegTree.h
//  myLib
//
//  Created by XinquanZhou on 6/28/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__SegTree__
#define __myLib__SegTree__

#include <iostream>
#include <vector>
#include <queue>
#include "MyExceptions.h"

template <class T>
class SegTreeNode {
public:
    int start, end;
    T data;
    SegTreeNode * left, *right;

    SegTreeNode(int start, int end): start(start), end(end), left(nullptr), right(nullptr){}
};

template <class T>
class SegTree {
    
public:
    typedef T (*comp)(const T & left, const T & right);

    SegTree(int start, int end);
    
    // users can build the segtree with a vector, optionally provide the ruling function pointer
    SegTree<T>(std::vector<T> & vec, comp cmp = nullptr);
    
    virtual ~SegTree<T>(){
        if (root) {
            _destroy(root);
        }
    }
    
    // to query the result with the interval
    T Query(int start, int end);
    
    // change the value of the tree
    void Update(int index, T value);
    
    // Print each node in the order of bfs
    void Print() const;
private:
    SegTreeNode<T> * root;
    
    // this is the rule of building segment tree, by default it will be a interval sum tree
    comp _cmp;
    
    SegTreeNode<T> * _build(int start, int end);
    
    
    SegTreeNode<T> * _build(std::vector<T> & vec, int start, int end);

    
    void _destroy(SegTreeNode<T> * root);
    T _query(SegTreeNode<T> * root, int start, int end);
    
    void _update(SegTreeNode<T> * root, int index, T value);
};



template <class T>
SegTreeNode<T> * SegTree<T>::_build(int start, int end) {
    if (end < start) {
        return nullptr;
    }
    SegTreeNode<T> * node = new SegTreeNode<T>(start, end);
    if (start != end) {
        int mid = (start+end)/2;
        node -> left = _build(start, mid);
        node -> right = _build(mid+1,start);
    }
    return node;
}

template <class T>
SegTreeNode<T> * SegTree<T>::_build(std::vector<T> & vec, int start, int end) {
    if (end < start) {
        return nullptr;
    }
    SegTreeNode<T> * node = new SegTreeNode<T>(start, end);
    int mid = (start + end) / 2;
    if (start == end) {
        node -> data = vec[start];
        return node;
    }
    else{
        node -> left = _build(vec, start, mid );
        node -> right = _build(vec, mid + 1, end);
    }
    if (_cmp) {
        node -> data = (*_cmp)(node->left->data, node->right -> data);
    }
    else{
        node -> data = node->left->data + node->right-> data;
    }
    return node;
}

template <class T>
void SegTree<T>::_destroy(SegTreeNode<T> * root) {
    if (root -> start == root -> end) {
        delete root;
        return;
    }
    if (root -> left) {
        _destroy(root->left);
    }
    if(root -> right){
        _destroy(root -> right);
    }
    delete root;
}

template <class T>
SegTree<T>::SegTree(int start, int end){
    try {
        if (end < start) {
            throw InvalidParams();
        }
        root = _build(start, end);
    } catch (InvalidParams & e) {
        throw;
    }
}

template <class T>
SegTree<T>::SegTree(std::vector<T> & vec, comp cmp ):_cmp(cmp){
    int start = 0, end = static_cast<int>(vec.size() - 1);
    root = _build(vec, start, end);
}


template <class T>
T SegTree<T>::_query(SegTreeNode<T> * root, int start, int end) {
    if (start == root->start && end == root->end) {
        return root->data;
    }
    
    int mid = (root->start + root->end) / 2;
    if (end <= mid) {
        return _query( root->left, start, end);
    }
    else if(start > mid){
        return _query(root->right, start,end);
    }
    else{
        if (_cmp) {
            return (*_cmp)(_query(root->left,start,mid), _query(root->right, mid+1, end));
        }
        else{
            return _query(root->left,start,mid) + _query(root->right, mid+1, end);
        }
    }
}

template <class T>
T SegTree<T>::Query(int start, int end) {
    try {
        if (end < start || start > root-> end || end < root->start) {
            throw InvalidParams();
        }
        return _query(root, start, end);
    } catch (InvalidParams & e) {
        throw;
    }
}

template <class T>
void SegTree<T>::_update(SegTreeNode<T> * root, int index, T value){
    if(root->start == root->end){
        root-> data = value;
        return;
    }
    int mid = (root -> start + root -> end) / 2;
    if (_cmp) {
        if(index <= mid && root->data == (*_cmp)(root->data, root->left->data)){
            // modify it and update the max value in that branch
            _update(root->left,index,value);
            // just take the new max
            root->data = (*_cmp)(root->left->data, root->right->data);
            
        }
        // right branch
        else if(index > mid && root->data == (*_cmp)(root->right -> data, root->data)){
            _update(root->right,index,value);
            root->data = (*_cmp)(root->left->data, root->right->data);
        }
    }
    else{
        if(index <= mid){
            // modify it and update the max value in that branch
            _update(root->left,index,value);
            root->data = (root->left->data + root->right->data);
            
        }
        // right branch
        else if(index > mid ){
            _update(root->right,index,value);
            root->data = (root->left->data + root->right->data);
        }
    }
//    if(index <= mid){
//        _update(root->left,index,value);
//        
//    }
//    else{
//        _update(root->right,index,value);
//        
//    }
}

template <class T>
void SegTree<T>::Update(int index, T value) {
    try {
        if (index < root->start || index > root->end) {
            throw InvalidParams();
        }
        _update(root, index, value);
    } catch (InvalidParams & e) {
        throw;
    }
}

template <class T>
void SegTree<T>::Print() const {
    std::queue<SegTreeNode<T> *> q;
    q.push(root);
    while (!q.empty()) {
        SegTreeNode<T> * cur = q.front();
        q.pop();
        std::cout << "< start = " << cur->start << ", end = " << cur->end << ", data = "<< cur->data << "> ";
        if (cur->left) {
            q.push(cur->left);
        }
        if(cur -> right) {
            q.push(cur->right);
        }
    }
}


#endif /* defined(__myLib__SegTree__) */
