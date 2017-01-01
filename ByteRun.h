#pragma once
#include "Algorithm.h"

class ByteRun : public Algorithm
{
private:
   pixel getPixel(unsigned int);
public:
	ByteRun(DataImage* di = nullptr);
    void compress();
    void decompress();
    ~ByteRun();
};


