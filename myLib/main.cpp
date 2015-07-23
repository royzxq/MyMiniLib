//
//  main.cpp
//  myLib
//
//  Created by XinquanZhou on 3/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//  This is an empty main function which does nothing


#include <string>
#include <vector>
#include <iostream>
#include <future>
#include <numeric>
//#include "LinkedList.h"
//#include "MinHeap.h"
#include <memory>
#include <mutex>
#include "SegTree.h"
#include "Trie.h"
#include <stack>
#include <unordered_set>
using namespace std;

int t = 0 ;
std::mutex mtx;
void P(){
    mtx.lock();
    cout << "timer equals " << t << endl;
    t++;
    mtx.unlock();
}
int m(const int & a, const int & b){
    return a > b ? a : b;
}

/**
 * Definition for a point.
 *
 */
struct Point {
 int x;
 int y;
 Point() : x(0), y(0) {}
 Point(int a, int b) : x(a), y(b) {}
};
class Solution {
public:
    /**
     * @param n an integer
     * @param m an integer
     * @param operators an array of point
     * @return an integer array
     */
    class Node{
    public:
        Node * parent;
        int rank, val;
        Node(){
            parent = nullptr;
            rank = 0;
        }
        Node(Node * parent){
            this -> parent = parent;
            rank = 0;
        }
    };
    
    unordered_set<Node*> roots;
    
    Node * makeSet(){
        Node * root = new Node();
        roots.insert(root);
        return root;
    }
    
    Node * Find(Node * x){
        while(x->parent != nullptr){
            x = x->parent;
        }
        return x;
    }
    
    void Union(Node * x, Node * y){
        Node * rx = Find(x);
        Node * ry = Find(y);
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
    
    };

int main(int argc, const char * argv[]) {
//    auto fut1 = async(P);
//    auto fut2 = async(P);
//    auto fut3 = async(P);
//    mtx.lock();
//    cout << "this is in the main "<<  t << endl;
//    mtx.unlock();
//    vector<int> v = {1,2,4,5,6};
////    typedef int (*maximum) (int &, int &);
//    SegTree<int>::comp funptr = & m;
//    SegTree<int> * st = new SegTree<int>(v, funptr);
//    st -> Print();
//    cout << endl;
//    st -> Update(2, 7);
//    st -> Print();
//    delete st;
////    cout << st->Query(0, 3);
//    return 1;
    
    string s = "12 + 3 * 4343 / 734 + 6";
    cout << 12 + 3 * 4343 / 734 + 6 << endl;
    return 1;
    
}



