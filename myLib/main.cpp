//
//  main.cpp
//  myLib
//
//  Created by XinquanZhou on 3/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include <iostream>
#include <string>
#include <new>
#include "playground.h"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
//    string s("haha");
//    string s2("this is s2");
//    string & rs = s;
//    string * ps = &s2;
//    cout << rs << endl;
    
//    cout << b << endl;
//    cout << a << endl;
//    cout << c << endl;
//    cout << d << endl;
//    cout << typeid(b).hash_code() << endl;
//    std::cout << "Hello, World!\n";
//    string * ps = new string("this is new mem");
//    
//    void * rawS = operator new (ps->length());
////    string * newps = static_cast<string*>(rawS);
//    string * placeNewps = new (rawS) string("this is new mem 2111");
//    cout<< ps -> length() <<endl;
//    cout<<sizeof(string) * ps->length() << endl;
//    cout<<sizeof(*ps) << endl;
//    cout << *placeNewps <<endl;
////    operator delete(rawS);
//    delete ps;
////    placeNewps -> ~string();
//    delete placeNewps;
//    string * psa = new string[10];
//    delete [] psa   ;
    Rational ** a = new Rational *[2];
    for (int i = 0 ; i < 2 ; ++i ) {
        a[i] = new Rational(i,i+1);
    }
    a[0] -> setS(3);
    cout << a[1] -> getS() <<endl;
    
    return 0;
}
