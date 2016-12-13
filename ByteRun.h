#pragma once
#include "Algorithm.h"

class ByteRun : public Algorithm
{
private:
   pixel getPixel(unsigned int);
public:
    ByteRun(std::string,int,int,bool);
    ~ByteRun();
    static void decompress(DataImage&);
    void compress();
    void saveToFile(std::string);
};


