#pragma once
#include "Algorithm.h"

class ByteRun : public Algorithm
{
private:
    pixel getPixel(unsigned int);
public:
    ByteRun(std::shared_ptr<DataImage> &data);
    void compress();
    void decompress();
    ~ByteRun();
};

