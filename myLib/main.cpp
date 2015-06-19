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
#include "LinkedList.h"
#include "MinHeap.h"
#include <memory>
#include <mutex>
using namespace std;

int t = 0 ;
std::mutex mtx;
void P(){
    mtx.lock();
    cout << "timer equals " << t << endl;
    t++;
    mtx.unlock();
}
int main(int argc, const char * argv[]) {
    auto fut1 = async(P);
    auto fut2 = async(P);
    auto fut3 = async(P);
    mtx.lock();
    cout << "this is in the main "<<  t << endl;
    mtx.unlock();
    return 1;
}
