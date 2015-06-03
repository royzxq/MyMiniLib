//
//  File_Reader.h
//  SoundHound_Challenge
//
//  Created by XinquanZhou on 2/12/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//


#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <sstream>

#define _FILE_MAXSTR 4096
#define _FILE_MAXFILE (_FILE_MAXSTR * 4096)


class FileReader{
protected:
    std::string _filename;
    std::string _row;
    std::string _emptystr;
    size_t _numcol = 0;
    
    FileReader();
public:
    typedef std::vector<std::string> row_type;
    row_type file_buf;
    row_type _split(const std::string s, char delim);
    bool strhaschar(const char * haystack, char needle);
    FileReader(const char * filename);
    ~FileReader();
};

class DictFile : public FileReader {
    typedef std::unordered_map<std::string, float> _dict_type;
    _dict_type _dict;
    void _parsebuf();
    row_type _elems;
    float _totalnum;
    
//    DictFile();
public:
    DictFile(const char * filename):FileReader(filename){
        _parsebuf();
    };
    std::vector<std::pair<std::string, float>> getvec(std::string s);
    float getProb(std::string s1);
    ~DictFile();
    
    
};

class InputFile : public FileReader{
    typedef std::vector<std::vector<std::string>> _matrixtype;
    _matrixtype _matrix;
    void _parsebuf();
    row_type _elems;
    _matrixtype _transpose();
    size_t _numstrips = 0;
    size_t _numlines = 0;
//    InputFile();
public:
    InputFile(const char * filename):FileReader(filename){
        _parsebuf();
    }
    ~InputFile();
    std::string getElem(size_t row, size_t col) const{
        std::string res;
        if (row >= _numlines || col >= _numstrips ) {
            printf("out of range\n");
            return res;
        }
        return _matrix[col][row];
    }
    row_type getCol(size_t n) const;
    size_t getStripNum() const {
        return _numstrips;
    }
    size_t getLineNum() const {
        return _numlines;
    }
};













