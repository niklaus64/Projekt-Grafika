#pragma once
#include "Algorithm.h"

class RLE : public Algorithm
{
public:
    virtual void compress();
    static void decompress(DataImage&);
    virtual void saveToFile(std::string);
    RLE(std::string, int, int, bool);
    ~RLE();
};

