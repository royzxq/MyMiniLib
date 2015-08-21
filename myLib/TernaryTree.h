//
//  TernaryTree.h
//  myLib
//
//  Created by XinquanZhou on 8/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__TernaryTree__
#define __myLib__TernaryTree__

#include <stdio.h>
#include <string>
#include <memory>

class TernaryTree {
private:
    struct TernaryTreeNode{
        char val;
        std::shared_ptr<TernaryTreeNode>  left = nullptr, right = nullptr, eq = nullptr;
        TernaryTreeNode(char v):val(v){}
    };
    
    std::shared_ptr<TernaryTreeNode> root = nullptr;
public:
    TernaryTree(){}
    ~TernaryTree(){};
    
    bool Search(const std::string& s);
    void Insert(const std::string& s);
    
    std::shared_ptr<TernaryTreeNode> insert(std::shared_ptr<TernaryTreeNode> ptr, char * s);
};

#endif /* defined(__myLib__TernaryTree__) */
