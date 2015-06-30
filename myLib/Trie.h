//
//  Trie.h
//  myLib
//
//  Created by XinquanZhou on 6/29/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__Trie__
#define __myLib__Trie__

#include <stdio.h>
#include <vector>





class TrieNode {
public:
    char val;
    bool exist;
    std::vector<TrieNode *> next;
    
    TrieNode(char c): val(c), exist(false){
        next.assign(26, nullptr);
    }
    
    TrieNode():exist(false){
        next.assign(26, nullptr);
    }
};


class Trie {
public:
    Trie():root(new TrieNode()){}
    Trie(std::string & s);
    virtual ~Trie(){
        _destroy(root);
    }
    
    void Insert(std::string& s);
    bool Search(std::string& key);
    bool StartWith(std::string& prefix);
    
private:
    TrieNode * root;
    void _destroy(TrieNode * node);
};



#endif /* defined(__myLib__Trie__) */
