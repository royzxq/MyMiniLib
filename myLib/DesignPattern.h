//
//  DesignPattern.h
//  myLib
//
//  Created by XinquanZhou on 10/13/15.
//  Copyright © 2015 Xinquan Zhou. All rights reserved.
//

#ifndef DesignPattern_h
#define DesignPattern_h
#include<iostream>
#include <set>
#include <string>
using namespace std;

/*
 1. Strategy pattern --> composition instead of inheritance
 */

class DummyBehavior {
public:
    virtual void behave() = 0;
    virtual ~DummyBehavior(){}
};

class Walk : public DummyBehavior{
public:
    void behave() override{
        cout << "I'm walking" << endl;
    }
};

class DummyBaseClass{
private:
    DummyBehavior * behavior;
public:
    DummyBaseClass(){
        behavior = nullptr;
    }
    
    virtual ~DummyBaseClass(){
        if(behavior){
            delete behavior;
            behavior = nullptr;
        }
    }
    void setBehavior(DummyBehavior * behavior){
        if( this->behavior ){
            delete this->behavior;
            this->behavior = nullptr;
        }
        this -> behavior = behavior;
    }
    void behave(){
        behavior -> behave();
    }
    virtual void display() = 0 ;
};

class WalkingClass: public DummyBaseClass{
public:
    WalkingClass(){
        setBehavior(new Walk());
    }
    void display() override{
        cout << "Displaying: ";
        behave();
    }
};
        
        
/*
 2. Observor pattern --> subject and obeservors, notifying and updating; using pulling updating
*/

class Observable;
        
class Observer{
protected:
    Observable * observable;
public:
    Observer(Observable * o);
    ~Observer();
    virtual void update(int) = 0;
    virtual void display() = 0;
};
        
class Observable {
protected:
    set<Observer *> observers;
public:
    void registerObserver(Observer* o){
        if(observers.find(o) == observers.end()){
            observers.insert(o);
        }
    }
    void removeObserver(Observer* o){
        if(observers.find(o) != observers.end()){
            observers.erase(o);
        }
    }
    virtual void notifyObservers() = 0 ;
};
        
Observer::Observer(Observable * o){
    observable = o;
    observable -> registerObserver(this);
}

Observer::~Observer(){
    observable -> removeObserver(this);
}
        
class DummyData : public Observable{
private:
    int dummyVal = 0;
public:
    void notifyObservers() override{
        for(auto x : observers){
            x -> update(dummyVal);
        }
    }
    void setVal(int a){
        dummyVal = a;
        notifyObservers();
    }
    int getVal() const{
        return dummyVal;
    }
};
        
class DummyObserver1 : public Observer{
private:
    int val1 = 0;
public:
    DummyObserver1(Observable * o): Observer(o){};
    void update(int data) override{
        val1 = data;
        display();
    }
    
    void display() override{
        cout << "the dummy observer1: " << val1  << endl;
    }
};


/*
 3. Decorator pattern --> wraping the class with another class
 */

class Decorator{
protected:
    string description = "Base class";
public:
    virtual ~Decorator(){}
    virtual string getDescription(){
        return description;
    }
    virtual void doSomething() = 0 ;
};

class Model1: public Decorator{
public:
    Model1(){
        description = "Model1";
    }
    void doSomething() override{
        cout << "This is model 1"<<endl;
    }
};

class Model2: public Decorator{
public:
    Model2(){
        description = "Model2";
    }
    void doSomething() override{
        cout << "This is model 2" << endl;
    }
};

class Component1 : public Decorator{
private:
    Decorator * decorator;
public:
    Component1(Decorator * d){
        decorator = d;
    }
    
    string getDescription() override{
        return decorator->getDescription() + ", Component1";
    }
    void doSomething() override{
        decorator -> doSomething();
        cout << "With Component1"<<endl;
    }
};
        
class Component2 : public Decorator{
private:
    Decorator * decorator;
public:
    Component2(Decorator * d){
        decorator = d;
    }
    string getDescription() override{
        return decorator->getDescription() + ", Component2";
    }
    void doSomething() override{
        decorator->doSomething();
        cout<< "With Component2" << endl;
    }
};


#endif /* DesignPattern_h */
