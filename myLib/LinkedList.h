//
//  LinkedList.h
//  myLib
//
//  Created by XinquanZhou on 6/8/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__LinkedList__
#define __myLib__LinkedList__

template <class T>
class Node {
public:
    T value;
    Node<T> * next;
    Node<T>(const T Val):value(Val),next(nullptr){}
    Node<T>(const Node<T> & CopyNode): value(CopyNode.value),next(nullptr){}
    
};

template <class T>
class SLinkedList {
private:
    void _DeleteNextNode(Node<T> * node);
public:
    Node<T> * head, *tail;

    SLinkedList(){
        head = nullptr;
        tail = nullptr;
    }
    SLinkedList(Node<T> * initNode):tail(initNode){
        head = new Node<T>();
        head -> next = tail;
    }
    
    virtual ~SLinkedList(){
        Node<T> * n = head;
        while (head) {
            head = head -> next;
            delete n;
            n = head;
        }
    }
    
    SLinkedList(const SLinkedList& CopyList);
    const SLinkedList<T>& operator+(const SLinkedList<T> & Addee);
    
    void InsertAfterTail(const T Val);
    void InsertAfterHead(const T Val);
    void DeleteByValue(const T Val);
    void DeleteNode(Node<T> * N);
    void Print() const;
    void PrintBackward() const;
    
    
};


#endif /* defined(__myLib__LinkedList__) */
