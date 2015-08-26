//
//  UnionFind.h
//  myLib
//
//  Created by XinquanZhou on 8/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef myLib_UnionFind_h
#define myLib_UnionFind_h

#include <set>

template<class T>
class Node{
public:
    Node * parent;
    int rank;
    T val;
    Node(){
        parent = nullptr;
        rank = 0;
    }
    Node(Node<T> * parent){
        this -> parent = parent;
        rank = 0;
    }
};


template <class T>
class UnionFind {
private:
    std::set<Node<T>*> roots;
    struct Deleter{
        void operator()(T * ptr){
            delete ptr;
        }
    };
    
public:
    ~UnionFind(){
        for_each(roots.begin(), roots.end(), Deleter());
    }
    Node<T> * makeSet(){
        Node<T> * root = new Node<T>();
        roots.insert(root);
        return root;
    }
    
    Node<T> * Find(Node<T> * x){
        while(x->parent != nullptr){
            x = x->parent;
        }
        return x;
    }
    
    void Union(Node<T> * x, Node<T> * y){
        Node<T> * rx = Find(x);
        Node<T> * ry = Find(y);
        if(rx->rank < ry -> rank){
            rx->parent = ry;
            roots.erase(rx);
        }
        else if(rx->rank > ry -> rank){
            ry->parent = rx;
            roots.erase(ry);
        }
        else{
            ry->parent = rx;
            rx -> rank ++;
            roots.erase(ry);
        }
    }
    int UnionSize() const{
        return roots.size();
    }

};



#endif
