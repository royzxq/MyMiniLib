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

using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> ves;
    for (int i = 10 ; i > 0 ; i--) {
        ves.push_back(i);
    }
    MinHeap<int> * mh = new MinHeap<int>(ves);

    for (int i = 0 ; i < 10; i++) {
        int j = mh -> DeleteMin();
        cout << j << " ";
    }
    
}
