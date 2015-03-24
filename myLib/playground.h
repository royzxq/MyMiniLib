//
//  playground.h
//  myLib
//
//  Created by XinquanZhou on 3/20/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef __myLib__playground__
#define __myLib__playground__

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class ALA {
public:
    ALA();
    virtual void processAdoption() = 0;
    virtual ~ALA();
};

class Puppy : public ALA{
public:
    virtual void processAdoption();
    virtual ~Puppy();
};

class Kitten : public ALA{
public:
    virtual void processAdoption();
    virtual ~Kitten();
};
template <class T>
class autoptr {
    T * ptr;
    
public:
    autoptr(T * p = 0) : ptr(p){}
    ~autoptr() {
        delete ptr;
    }
};
auto_ptr<ALA> readALA(istream & s);

void processAdoption(istream & s){
    while (s) {
        auto_ptr<ALA> pA = readALA(s);
        try {
            pA -> processAdoption();
        } catch (exception &e) {
            throw;
        }
        
    }
}

class EquipmentPiece {
    int IDNumber;
    static const int UNDEFINED = 0;
//    EquipmentPiece();
public:
//    EquipmentPiece():IDNumber(0){};
    EquipmentPiece(int IDNumber = UNDEFINED):IDNumber(IDNumber){};
    

};
//EquipmentPiece::UNDEFINED = 0;
EquipmentPiece a ;
EquipmentPiece * best[10];
void * rawMemory = operator new[](10 * sizeof(EquipmentPiece));
EquipmentPiece * B = static_cast<EquipmentPiece*>(rawMemory);
template<class T>
class Array {
    T * data;
    
public:
    Array(int size);
};

template<class T>
Array<T>::Array(int size){
    data = new T[size];
}

class Image {
    
    
public:
    Image(const string & imageDataFileName);
};

class AudioClip {
    
    
public:
    AudioClip(const string & audioDataFileName);
};


class bookEntry {
    string theName;
    const auto_ptr<Image > theImage;
    const auto_ptr<AudioClip > theAudio;
//    AudioClip * const theAudio;
//    void cleanup(){
//        delete theAudio;
//        delete theImage;
//    }
//    Image * initImage(const string & imageFileName){
//        if (imageFileName != "") {
//            return new Image(imageFileName);
//        }
//        else return 0;
//    }
//    AudioClip * initAudio(const string & audioFileName){
//        try {
//            if (audioFileName != "") {
//                return  new AudioClip(audioFileName);
//                
//            }
//            else return 0;
//        } catch (exception & e) {
//            delete theImage;
//            throw;
//        }
//        
//    }
    
public:
    bookEntry(const string & name, const string & imageFileName = "", const string & audioFileName = ""):theName(name),theImage(imageFileName == "" ? 0 : new Image(imageFileName)),theAudio(audioFileName == "" ? 0:new AudioClip(audioFileName)){
                
    };
    
    ~bookEntry(){
//        cleanup();
    }
    
};

class Session {
    static void logCreation(Session * objAddr);
    static void logDestroy(Session * objAddr);
    
public:
    Session();
    ~Session();
};
Session::~Session(){
    try {
        logDestroy(this);
    } catch (exception & e) {
//        cerr << "something wrong with the constructor"<<endl;
    }
    
}

typedef void (*CallBackPtr) (int, int, void *) ;

class CallBack{
    CallBackPtr func;
    void * data;
public:
    CallBack(CallBackPtr fPtr, void * dataToPassBack):func(fPtr),data(dataToPassBack){}
    void makeCallBack(int x, int y) const throw();
};

void CallBack::makeCallBack(int x, int y) const throw(){
    func(x,y,data);
}



class Rational{
    double value;
    int num,den;
    int i;
    static int s;
public:
    Rational(int num = 0 , int den = 1):value(static_cast<double>(num) / den), num(num),den(den){
        i = 1;
        i++;
    };
    void setS(const int & a){
        s = a;
    }
    int getS() const{
        return s;
    }
    operator double() const{
        cout<<*this<<endl;
        return value;
    }
    ostream & operator<<(ostream &c) {
        return c << this->num << "/" << this->den <<endl;
    }
};
void playGround(){
    string * ps = new string("this is new mem");
    void * rawS = operator new (sizeof(string) * ps->length());
    string * newps = static_cast<string*>(rawS);
    string * placeNewps = new (rawS) string("this is new mem");
}
    
    
        
        
        
        
        
        
        
        
#endif /* defined(__myLib__playground__) */
