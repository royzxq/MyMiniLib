//
//  SegTreeTest.h
//  myLib
//
//  Created by XinquanZhou on 6/28/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef myLib_SegTreeTest_h
#define myLib_SegTreeTest_h
#include <algorithm>
#include "gtest/gtest.h"
#include "SegTree.h"
using namespace std;

int max_func(const int & a, const int & b){
    return a > b ? a : b;
}


TEST(stTest, QUERY){
    vector<int> v = {1,2,4,5,6};
    vector<vector<int>> sum(v.size(), vector<int> (v.size(), 0));
    SegTree<int> * st = new SegTree<int>(v);
    for (int i = 0 ; i < v.size(); ++i) {
        for (int j = i ; j < v.size(); j++) {
            if(i == j){
                sum[i][j] = v[i];
            }
            else{
                sum[i][j] = sum[i][j-1] + v[j];
            }
            EXPECT_EQ(st->Query(i,j),sum[i][j]);

        }
    }
    delete st;
}


TEST(stTest, QUERYII){
    vector<int> v = {1,2,4,5,6};
    vector<vector<int>> m(v.size(), vector<int> (v.size(), 0));
    SegTree<int>::comp funptr = & max_func;
    SegTree<int> * st = new SegTree<int>(v, funptr);
    for (int i = 0 ; i < v.size(); ++i) {
        for (int j = i ; j < v.size(); j++) {
            if(i == j){
                m[i][j] = v[i];
            }
            else{
                m[i][j] = max(m[i][j-1], v[j]);
            }
            EXPECT_EQ(st->Query(i,j),m[i][j]);
        }
    }
    delete st;
}

TEST(stTest, UPDATE){
    vector<int> v = {1,2,4,5,6};
    vector<vector<int>> sum(v.size(), vector<int> (v.size(), 0));
    SegTree<int> * st = new SegTree<int>(v);
    st -> Update(0, 3);
    v[0] = 3;
    for (int i = 0 ; i < v.size(); ++i) {
        for (int j = i ; j < v.size(); j++) {
            if(i == j){
                sum[i][j] = v[i];
            }
            else{
                sum[i][j] = sum[i][j-1] + v[j];
            }
            EXPECT_EQ(st->Query(i,j),sum[i][j]);
            
        }
    }
    delete st;
}

#endif
