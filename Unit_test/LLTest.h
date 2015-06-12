//
//  LLTest.h
//  myLib
//
//  Created by XinquanZhou on 6/10/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__LLTest__
#define __myLib__LLTest__

#include <stdio.h>
#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(LLTest, InsertTest){
    SLinkedList<int> * iList;
    iList = new SLinkedList<int> ();
    for (int i = 0 ; i < 100; i++) {
        iList->InsertAfterTail(i);
    }
    EXPECT_EQ(iList->GetLength(), 100);
    std::vector<int> Vec;
    iList->Flush(Vec);
    for (int i = 0 ; i < 100 ; i++) {
        EXPECT_EQ(Vec[i], i);
    }
    delete iList;
    iList = new SLinkedList<int>();
    for (int i = 0 ; i < 100; i++) {
        iList->InsertAfterHead(i);
    }
    iList -> Flush(Vec);
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(Vec[99-i], i);
    }
    delete iList;
    
    SLinkedList<float> * fList;
    fList = new SLinkedList<float> ();
    for (int i = 0 ; i < 100; i++) {
        iList->InsertAfterTail(float(i)/2);
    }
    EXPECT_EQ(iList->GetLength(), 100);
    std::vector<float> fVec;
    fList->Flush(fVec);
    for (int i = 0 ; i < 100 ; i++) {
        EXPECT_EQ(fVec[i], float(i)/2);
    }
    delete fList;
    fList = new SLinkedList<float>();
    for (int i = 0 ; i < 100; i++) {
        fList->InsertAfterHead(float(i)/2);
    }
    fList -> Flush(fVec);
    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(Vec[99-i], float(i)/2);
    }
    delete fList;
    
}
TEST(LLTest, DeleteTest){
    SLinkedList<int> * iList;
    std::vector<int> Vec;
    iList = new SLinkedList<int> ();
    for (int i = 0 ; i < 100; i++) {
        iList->InsertAfterTail(i);
    }
    iList -> DeleteByValue(0);
    iList -> Flush(Vec);
    for (int i = 1 ; i < 100; i++) {
        EXPECT_EQ(Vec[i-1], i);
    }
    iList -> DeleteByValue(99);
    for (int i = 1; i < 99; i++) {
        EXPECT_EQ(Vec[i-1], i);
    }
    iList -> InsertAfterHead(0);
    iList -> InsertAfterTail(99);
    
    iList -> DeleteByPos(0);
    iList -> Flush(Vec);
    for (int i = 1 ; i < 100; i++) {
        EXPECT_EQ(Vec[i-1], i);
    }
    iList -> DeleteByPos(iList->GetLength()-1);
    for (int i = 1; i < 99; i++) {
        EXPECT_EQ(Vec[i-1], i);
    }
    iList -> InsertAfterHead(0);
    iList -> InsertAfterTail(99);
    
    delete iList;
    iList = new SLinkedList<int>();
    for (int i = 0 ; i < 100 ; i++) {
        iList -> InsertAfterTail(1);
    }
    iList -> DeleteByValue(1);
    iList -> Flush(Vec);
    EXPECT_EQ(Vec.size(), 0);
    delete iList;
}

TEST(LLTest, CopyTest){
    SLinkedList<int> * iList;
    std::vector<int> Vec;
    iList = new SLinkedList<int> ();
    for (int i = 0 ; i < 100; i++) {
        iList->InsertAfterTail(i);
    }
    SLinkedList<int> * copyList = iList;
    copyList->Flush(Vec);
    for (int i = 0 ; i < 100 ; i++) {
        EXPECT_EQ(Vec[i], i);
    }
}
#endif /* defined(__myLib__LLTest__) */
