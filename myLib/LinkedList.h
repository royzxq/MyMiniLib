//
//  LinkedList.h
//  myLib
//
//  Created by XinquanZhou on 6/8/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__LinkedList__
#define __myLib__LinkedList__

#include <vector>
#include <iostream>
#include <stack>
#include "MyExceptions.h"
//using namespace::std;


// Node class for linkedlist
template <class T>
class Node {
public:
    T value;
    Node<T> * next, *prev;
    Node<T>():value(0),next(nullptr),prev(nullptr){}
    Node<T>(const T Val):value(Val),next(nullptr),prev(nullptr){}
    Node<T>(const Node<T> & CopyNode): value(CopyNode.value),next(nullptr),prev(nullptr){}
};



// the single linked linkedlist API
template <class T>
class SLinkedList {
private:
    void _DeleteNextNode(Node<T> * Node);
protected:
    size_t _length;
    void _Destroy();
public:
    Node<T> * head, *tail;

    SLinkedList(){
        head = new Node<T>();
        tail = nullptr;
        _length = 0;
    }
    
    SLinkedList(Node<T> * initNode):tail(initNode){
        head = new Node<T>();
        head -> next = tail;
        _length = 1;
    }
    
    virtual ~SLinkedList(){
        _Destroy();
    }
    
    SLinkedList(const SLinkedList& CopyList);
    
    const SLinkedList<T>& operator+(const SLinkedList<T> & Addee);
    
    size_t GetLength() const{
        return _length;
    }
    
    virtual void InsertAfterTail(const T Val);
    
    virtual void InsertAfterHead(const T Val);
    
    virtual void DeleteByValue(const T Val);
    
    virtual void DeleteNode(Node<T> * N);
    
    virtual void DeleteByPos(int Pos);
    
    void Print() const;
    
    virtual void PrintBackward() const;
    
    void Flush(std::vector<T> & Vec);
    
};

// the double linked linkedlist API
template <class T>
class DLinkedList : public SLinkedList<T> {
private:
    void _DeleteNode(Node<T> * Node);
public:
    DLinkedList():SLinkedList<T>(){}
    DLinkedList(Node<T> * initNode):SLinkedList<T>(initNode){
        this-> tail -> prev = this -> head;
    }
    
    virtual ~DLinkedList();
    
    virtual void InsertAfterTail(const T Val);
    
    virtual void InsertAfterHead(const T Val);
    
    virtual void DeleteByValue(const T Val);
    
    virtual void DeleteNode(Node<T> * N);
    
    virtual void DeleteByPos(int Pos);
    
    virtual void PrintBackward() const;
};


template <class T>
void SLinkedList<T>::_Destroy() {
    while (head) {
        Node<T> * n = head;
        if (n) {
            delete n;
        }
        head = head -> next;
    }
}

template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList<T> & CopyList) {
    head = nullptr;
    Node<T> * cur = CopyList.head;
    if (!head && cur) {
        head = new Node<T>(cur->value);
        tail = head;
        cur = cur -> next;
    }
    while (cur) {
        Node<T> * node  = new Node<T>(cur->value);
        tail -> next = node;
        tail = node;
        cur = cur -> next;
    }
    _length = CopyList.GetLength();
}

template <class T>
const SLinkedList<T>& SLinkedList<T>::operator+(const SLinkedList<T> &Addee) {
    Node<T> * Cur = head;
    Node<T> * Cur_Addee = Addee.head;
    while (Cur != tail && Cur_Addee!=Addee.tail) {
        Cur -> next -> value += Cur_Addee -> next ->value;
        Cur_Addee = Cur_Addee -> next;
        Cur = Cur -> next;
    }
    return *this;
}



template <class T>
 void SLinkedList<T>::InsertAfterTail(const T Val) {
    Node<T> * node = new Node<T>(Val);
    _length ++;
    if (!tail) {
        head -> next =node;
        tail = node;
        return;
    }
    tail -> next = node;
    tail = node;
}


template <class T>
 void SLinkedList<T>::InsertAfterHead(const T Val) {
    Node<T> * node = new Node<T>(Val);
    _length ++;
    if (!tail) {
        head -> next = node;
        tail = node;
        return;
    }
    node -> next = head -> next;
    head -> next = node;
}

template <class T>
 void SLinkedList<T>::_DeleteNextNode(Node<T> *node) {
    _length --;
    if (node->next == tail) {
        node -> next = nullptr;
        delete tail;
        tail = node;
        return;
    }
    Node<T> * next = node->next;
    node -> next = next -> next;
    delete next;
}

template <class T>
 void SLinkedList<T>::DeleteByValue(const T Val) {
    Node<T> * cur = head;
    while (cur != tail) {
        if (cur->next->value == Val) {
            _DeleteNextNode(cur);
        }
        else{
            cur = cur -> next;
        }
    }
}

template <class T>
 void SLinkedList<T>::DeleteNode(Node<T> *N) {
    if (N == head) {
        return;
    }
    Node<T> * cur = head;
    while (cur) {
        if (cur->next == N) {
            _DeleteNextNode(cur);
            return;
        }
        else{
            cur = cur -> next;
        }
    }
}

template <class T>
void SLinkedList<T>::Print() const {
    Node<T> * cur = head;
    while (cur!=tail) {
        std::cout << cur-> next -> value << " ";
        cur = cur -> next;
    }
}

template <class T>
 void SLinkedList<T>::PrintBackward() const {
     std::stack<T> st;
    Node<T> * cur = head;
    while (cur!=tail) {
        st.push(cur->next -> value);
        cur = cur -> next;
    }
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
}

template <class T>
 void SLinkedList<T>::DeleteByPos(int Pos) {
    try {
        if (Pos >= _length || Pos < 0) {
            throw BeyondBoundry();
        }
        Node<T> * cur = head;
        int curPos = 0;
        while (cur!=tail) {
            if (curPos++ == Pos) {
                _DeleteNextNode(cur);
                return;
            }
            cur = cur -> next;
        }
    } catch (std::exception & e) {
        throw;
    }
}

template <class T>
void SLinkedList<T>::Flush(std::vector<T> &Vec) {
    Vec.clear();
    Node<T> * cur = head;
    while (cur != tail) {
        Vec.push_back(cur->next->value);
        cur = cur -> next;
    }
}


template <class T>
DLinkedList<T>::~DLinkedList() {
    this -> _Destroy();
}

template <class T>
void DLinkedList<T>::InsertAfterTail(const T Val) {
    Node<T> * node = new Node<T>(Val);
    this -> _length ++;
    if (!this -> tail) {
//        node -> next = this -> tail;
//        this -> head = node;
//        this -> tail = node;
        this -> head -> next = node ;
        node -> prev = this -> head;
        this -> tail = node;
        return;
    }
    this -> tail -> next = node;
    node -> prev = this -> tail;
    this -> tail = node;
}

template <class T>
void  DLinkedList<T>::InsertAfterHead(const T Val) {
    Node<T> * node = new Node<T>(Val);
    this -> _length ++;
    if (!this->tail) {
        this -> head -> next = node;
        node -> prev = this -> head;
        this -> tail = node;
        return;
    }
    node -> next = this -> head -> next;
    this -> head -> next = node;
    node -> next -> prev = node;
    node -> prev = this -> head;
    
}

template <class T>
void DLinkedList<T>::_DeleteNode(Node<T> *Node) {
    Node -> prev -> next = Node -> next;
    Node -> next -> prev = Node -> prev;
    delete Node;
}

template <class T>
void DLinkedList<T>::DeleteNode(Node<T> *N) {
    if (N == this -> head) {
        return;
    }
    Node<T> * cur = this->head;
    while (cur) {
        if (cur == N) {
            _DeleteNode(cur);
            this -> _length -- ;
            return;
        }
        else{
            cur = cur -> next;
        }
    }
}

template <class T>
void DLinkedList<T>::DeleteByValue(const T Val) {
    Node<T> * cur = this->head->next;
    while (cur != this -> tail) {
        if (cur->value == Val) {
            Node<T> * node_to_be_delete = cur;
            cur = cur -> next;
            _DeleteNode(node_to_be_delete);
            this -> _length -- ;

        }
        else{
            cur = cur -> next;
        }
    }
    if (this -> tail -> value == Val) {
        cur = this -> tail;
        this -> tail = this -> tail -> prev;
        this -> _length -- ;
        delete cur;
    }

}

template <class T>
void  DLinkedList<T>::DeleteByPos(int Pos) {
    try {
        if (Pos >= this-> _length || Pos < 0) {
            throw BeyondBoundry();
        }
        Node<T> * cur = this -> head -> next;
        int curPos = 0;
        while (cur!=this -> tail) {
            if (curPos++ == Pos) {
                _DeleteNode(cur);
                this -> _length -- ;
                return;
            }
            cur = cur -> next;
        }
    } catch (std::exception & e) {
        throw;
    }
}

template <class T>
void DLinkedList<T>::PrintBackward() const{
    Node<T> * cur = this -> tail;
    if (!cur) {
        return;
    }
    while (cur != this -> head) {
        std::cout << cur -> value << " ";
        cur = cur -> prev;
    }
}


#endif /* defined(__myLib__LinkedList__) */
