#pragma once
#include "Algorithm.h"

class RLE : public Algorithm
{
public:
	virtual void compress();
	virtual void decompress();
	virtual void saveToFile(const std::string);
	RLE(std::string, int, int, bool);
	~RLE();
};

