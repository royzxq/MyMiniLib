//
//  File_Reader.cpp
//  SoundHound_Challenge
//
//  Created by XinquanZhou on 2/12/15.
//  Copyright (c) 2015 Xinquan Zhou. All rights reserved.
//

#include "File_Reader.h"

FileReader::FileReader(const char * filename){
    _filename = filename;
    std::ifstream file(filename);
    while (std::getline(file,_row)) {
        file_buf.push_back(_row);
        _numcol ++;
    }
}

FileReader::~FileReader(){
}


FileReader::row_type FileReader::_split(const std::string s, char delim){
    std::stringstream ss(s);
    std::string item;
    row_type elems;
    while (std::getline(ss, item, delim)) {
        if (item.empty()) {
            continue;
        }
        elems.push_back(item);
    }
    return elems;
}

bool FileReader::strhaschar(const char *haystack, char needle){
    for (int i = 0; haystack[i]; ++i) {
        if (haystack[i] == needle) {
            return true;
        }
    }
    return false;
}

void DictFile::_parsebuf(){
    for (int i = 0 ; i < _numcol; i++) {
        _elems = _split(file_buf[i], ' ');
        if (_elems.size() != 4) {
            printf("wrong dict format\n");
            return;
        }
        if (i == 0) {
            _totalnum = stof(_elems[0]);
        }
        else{
            float denom = stof(_elems[0]);
            if(denom < 7) continue;
            float ratio = denom / _totalnum;
            
            
            if (_dict.find(_elems[1]) == _dict.end()) {
                _dict[_elems[1]] = ratio;
            }
        }
        
    }
}

float DictFile::getProb(std::string s1) {
    if (_dict.find(s1) == _dict.end()) {
        return 0.0001;
    }
    else{
        return _dict[s1];
    }
}

void InputFile::_parsebuf(){
    for (int i = 0 ; i < _numcol; i++) {
        _elems = _split(file_buf[i], '|');
//        _elems.erase(_elems.begin());
//        _elems.pop_back();
        _matrix.push_back(_elems);
    }
    _numlines = _matrix.size();
    _numstrips = _matrix[0].size();
    _matrix = _transpose();
    
    
    
}

InputFile::_matrixtype InputFile::_transpose(){
    _matrixtype outtrans(_numstrips,std::vector<std::string>(_numlines));
    for(size_t i = 0 ; i < _numlines; ++i){
        for (size_t j = 0 ; j < _numstrips; ++j) {
            outtrans[j][i]  = _matrix[i][j];
        }
    }
    return outtrans;
}

FileReader::row_type InputFile::getCol(size_t n) const{
    if (n < _numstrips) {
        return _matrix[n];
    }
    else return row_type();
}









