//
//  VirtualConstructor.h
//  myLib
//
//  Created by XinquanZhou on 3/24/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__VirtualConstructor__
#define __myLib__VirtualConstructor__

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class NLComponent{
public:
    NLComponent(){};
    virtual ~NLComponent() ;
    virtual NLComponent * clone() const = 0;
    virtual ostream & print(ostream  & s) const = 0;
};

class TextBlock : public NLComponent{
public:
    virtual TextBlock * clone() const{
        return new TextBlock(*this);
    }
    virtual ostream & print(ostream & s) const;
};

class Graph : public NLComponent{
    virtual Graph * clone() const{
        return new Graph(*this);
    }
    virtual ostream & print(ostream & s) const;
};
inline
ostream & operator << (ostream & os, const NLComponent & nl){
    return nl.print(os);
}

class NewsLetter{
public:
    NewsLetter(){};
    NewsLetter(istream & s);
    NewsLetter(const NewsLetter & rhs);
    static NLComponent * readComponent( istream & str);
private:
    vector<NLComponent*> components;
};

NewsLetter::NewsLetter(const NewsLetter & rhs){
    for (int i = 0  ; i < rhs.components.size(); i++) {
        components.push_back(rhs.components[i]->clone());
    }
}



NewsLetter::NewsLetter(istream & s){
    while (s) {
        components.push_back(readComponent(s));
    }
}




#endif /* defined(__myLib__VirtualConstructor__) */
