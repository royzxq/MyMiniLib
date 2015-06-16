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
    virtual const char * what() const throw(){
        return "The input parameter is out of boundry";
    }
} myBeyondBoundry;


class FailInit : public std::exception {
    virtual const char * what() const throw(){
        return "Something wrong when you initialize objects";
    }
} myFailInit;

class FileIOError : public std::exception{
    virtual const char * what() const throw(){
        return "Something wrong when reading or writing files";
    }
} myFileIOError;

class InvalidParams : public std::exception{
    virtual const char * what() const throw(){
        return "The parameters are not allowed";
    }
} myInvalidParams;

#endif
