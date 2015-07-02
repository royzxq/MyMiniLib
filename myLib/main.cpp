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
int main(int argc, const char * argv[]) {
//    auto fut1 = async(P);
//    auto fut2 = async(P);
//    auto fut3 = async(P);
//    mtx.lock();
//    cout << "this is in the main "<<  t << endl;
//    mtx.unlock();
    vector<int> v = {1,2,4,5,6};
//    typedef int (*maximum) (int &, int &);
    SegTree<int>::comp funptr = & m;
    SegTree<int> * st = new SegTree<int>(v, funptr);
    st -> Print();
    cout << endl;
    st -> Update(2, 7);
    st -> Print();
    delete st;
//    cout << st->Query(0, 3);
    return 1;
}
