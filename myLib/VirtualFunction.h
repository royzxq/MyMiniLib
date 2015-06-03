////
////  VirtualFunction.h
////  myLib
////
////  Created by XinquanZhou on 3/30/15.
////  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
////
//
//#ifndef __myLib__VirtualFunction__
//#define __myLib__VirtualFunction__
//
//#include <stdio.h>
//#include <unordered_map>
//
//using namespace std;
//class SpaceShip;
//class SpaceStation;
//class Asteroid;
//
//class GameObject {
//public:
//    virtual void collide(GameObject & otherObj) = 0 ;
//    virtual void collide(SpaceShip & ) = 0 ;
//    virtual void collide(SpaceStation &) = 0 ;
//    virtual void collide(Asteroid & ) = 0;
//};
//
//
//class SpaceShip: public GameObject {
//private:
//    typedef void (SpaceShip::*hitFunctionPtr) (GameObject &);
//    typedef std::unordered_map<std::string, hitFunctionPtr> hitMap;
//    static hitFunctionPtr lookup( GameObject & wahtWeHit);
//
//public:
//    virtual void collideObj(GameObject & otherObj) ;
//    virtual void collideShip(SpaceShip & )  ;
//    //virtual void collideStation(SpaceStation &)  ;
////    virtual void collideAsteroid(Asteroid & ) ;
//    static hitMap initialze();
//
//};
//
//SpaceShip::hitFunctionPtr SpaceShip::lookup(GameObject &wahtWeHit) {
//    static hitMap collideMap = initialze();
//}
//
//SpaceShip::hitMap SpaceShip::initialze(){
//    hitMap * phm = new unordered_map<string,hitFunctionPtr>();
//    (*phm)["SpaceShip"] = &SpaceShip::collideShip;
//    
//}
//
//void SpaceShip::collide(GameObject & otherObj){
////    otherObj.collide(*this);
//    hitFunctionPtr hfp = lookup(otherObj);
//    if (hfp) {
//        (this -> *hfp) (otherObj);
//    }
//    else{
//        throw ;
//    }
//}
//
//class SpaceStation: public GameObject {  };
//class Asteroid: public GameObject {  };
//
//void checkForCollision(GameObject & obj1, GameObject & obj2);
//
//
//
//#endif /* defined(__myLib__VirtualFunction__) */
