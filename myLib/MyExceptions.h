//
//  MyExceptions.h
//  myLib
//
//  Created by XinquanZhou on 6/14/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#ifndef myLib_MyExceptions_h
#define myLib_MyExceptions_h
#include <exception>

class BeyondBoundry : public std::exception {
    virtual const char * what() const throw();
};


class FailInit : public std::exception {
    virtual const char * what() const throw();
} ;

class FileIOError : public std::exception{
    virtual const char * what() const throw(){
        return "Something wrong when reading or writing files";
    }
} ;

class InvalidParams : public std::exception{
    virtual const char * what() const throw();
} ;


class NoValidOp : public std::exception{
    virtual const char * what() const throw();
}; 
#endif
