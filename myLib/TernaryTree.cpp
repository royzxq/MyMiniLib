//
//  TernaryTree.cpp
//  myLib
//
//  Created by XinquanZhou on 8/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include "TernaryTree.h"


bool TernaryTree::Search(const std::string &s){
    std::shared_ptr<TernaryTreeNode> cur = root;
    int curIdx = 0;
    while (cur) {
        if (s[curIdx] < cur -> val) {
            if (!cur->left) {
                return false;
            }
            cur = cur -> left;
        }
        else if(s[curIdx] > cur -> val){
            if (!cur -> right) {
                return false;
            }
            cur = cur -> right;
        }
        else{
            curIdx ++;
            if (curIdx == s.length()) {
                return true;
            }
            cur = cur -> eq;
        }
    }
    return false;
}

void TernaryTree::Insert(const std::string &s){
//    if (!root) {
//        std::shared_ptr<TernaryTreeNode> cur (new TernaryTreeNode(s[0]));
//        root = cur;
//    }
    if (s.empty()) {
        return;
    }
//    std::shared_ptr<TernaryTreeNode> cur = root;
//    for (int i = 0 ; i < s.length(); i++) {
//        if (!cur) {
//            cur = std::shared_ptr<TernaryTreeNode>( new TernaryTreeNode(s[i]));
//        }
//        if (s[i] == cur -> val) {
//            cur = cur -> eq;
//        }
//        else if(s[i] < cur -> val){
//            cur = cur -> left;
//            i --;
//        }
//        else {
//            cur = cur -> right;
//            i --;
//        }
//    }
    char * c = const_cast<char *>(s.c_str()) ;
    insert(root, c);
}

std::shared_ptr<TernaryTree::TernaryTreeNode> TernaryTree::insert(std::shared_ptr<TernaryTreeNode> ptr, char *s){
    if (!ptr) {
        ptr = std::shared_ptr<TernaryTreeNode>( new TernaryTreeNode(*s));
    }
    if (ptr -> val > *s) {
        ptr->left = insert(ptr->left, s);
    }
    else if(ptr -> val < *s){
        ptr -> right = insert(ptr->right, s);
    }
    else{
        if (*s !=0) {
            ptr -> eq = insert(ptr -> eq, ++s);
        }
    }
    return ptr;
    
}