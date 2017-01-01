#pragma once
#include "Algorithm.h"

class RLE : public Algorithm
{
public:
	RLE(DataImage* di = nullptr);
    virtual void compress();
    virtual void decompress();
    ~RLE();
};

