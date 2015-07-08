//
//  Trie.cpp
//  myLib
//
//  Created by XinquanZhou on 6/29/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include "Trie.h"
#include <string>
#include "MyExceptions.h"

void Trie::Insert(std::string& s){
//    TrieNode* cur = root;
    std::shared_ptr<TrieNode> cur = root;
    for (auto c : s) {
        try {
            int index = static_cast<int>(c - 'a');
            if (index < 26 && index >= 0) {
                if (!cur->next[index]) {
//                    TrieNode * new_node = new TrieNode(c);
                    std::shared_ptr<TrieNode> new_node(new TrieNode(c));
                    cur -> next[index] = new_node;
                    cur = new_node;
                }
                else{
                    cur = cur -> next[index];
                }
            }
            else{
                throw InvalidParams();
            }
        } catch (InvalidParams & e ) {
            throw ;
        }
    }
    cur -> exist = true;
}

Trie::Trie(std::string &s):root(new TrieNode()){
    Insert(s);
}

bool Trie::Search(std::string &key){
    std::shared_ptr<TrieNode> cur = root;
    try {
        for (auto c : key) {
            int index = static_cast<int>(c - 'a');
            if (index < 26 && index >= 0) {
                if (!cur->next[index]) {
                    return false;
                }
                else{
                    cur = cur->next[index];
                }
            }
            else{
                throw InvalidParams();
            }
        }
        return cur->exist;
    } catch (InvalidParams & e) {
        throw ;
    }
}


bool Trie::StartWith(std::string &prefix){
    std::shared_ptr<TrieNode> cur = root;
    try {
        for (auto c : prefix) {
            int index = static_cast<int>(c - 'a');
            if (index < 26 && index >= 0) {
                if (!cur->next[index]) {
                    return false;
                }
                else{
                    cur = cur->next[index];
                }
            }
            else{
                throw InvalidParams();
            }
        }
        return true;
    } catch (InvalidParams & e) {
        throw ;
    }
}

//void Trie::_destroy(TrieNode * node){
//    for (int i = 0 ; i < 26 ; i ++) {
//        if (!node->next[i]) {
//            continue;
//        }
//        _destroy(node->next[i]);
//    }
//    delete node;
//}

