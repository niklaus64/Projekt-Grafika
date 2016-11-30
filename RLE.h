#pragma once
#include "Algorithm.h"

class RLE : public Algorithm
{
public:
	virtual void compress();
	virtual void decompress();
	RLE();
	~RLE();
};

