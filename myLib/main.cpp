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
using namespace std;

template <class T>
int parallel_sum(T s, T e) {
    auto len = e - s;
    if(len < 1000){
        return accumulate(s, e, 0)  ;
        
    }
    auto mid = s + len/3;
    auto mid2 = e - len/3;
    auto fut1 = async(parallel_sum<T>, mid,mid2);
    auto fut2 = async(parallel_sum<T>, mid2,e);

    int sum = parallel_sum(s, mid);
    return sum + fut1.get() + fut2.get();
}
int main(int argc, const char * argv[]) {
    vector<int> v(100000,1);
    int a = 0;
    int mask = 1;
    mask = mask << 3;
    a = a | mask;
    int res;
    
    cout<<a<<endl;
    //cout<<parallel_sum(v.begin(), v.end())<<endl;
    return 0;
}
