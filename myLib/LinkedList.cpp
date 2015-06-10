//
//  LinkedList.cpp
//  myLib
//
//  Created by XinquanZhou on 6/8/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//
#include <iostream>
#include <stack>
#include "LinkedList.h"

using namespace::std;

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
void SLinkedList<T>::InsertAfterTail(const T val) {
    Node<T> * node = new Node<T>(val);
    if (!tail) {
        node -> next = tail;
        head = node;
        tail = node;
        return;
    }
    tail -> next = node;
    tail = node;
}


template <class T>
void SLinkedList<T>::InsertAfterHead(const T val) {
    Node<T> * node = new Node<T>(val);
    if (!head) {
        head = new Node<T>();
        head -> next = node;
        tail = node;
        return;
    }
    Node<T> * n = head -> next;
    head -> next = node;
    node -> next = n;
}

template <class T>
void SLinkedList<T>::_DeleteNextNode(Node<T> *node) {
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
    while (cur) {
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
        cout << cur->next -> value << " ";
        cur = cur -> next;
    }
}

template <class T>
void SLinkedList<T>::PrintBackward() const {
    stack<T> st;
    Node<T> * cur = head;
    while (cur!=tail) {
        st.push(cur->next -> value);
        cur = cur -> next;
    }
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
}



