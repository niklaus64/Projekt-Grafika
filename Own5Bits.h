#pragma once
#include "Algorithm.h"


class Own5Bits : public Algorithm
{
public:
	Own5Bits(DataImage* di = nullptr);
	virtual void compress();
	virtual void decompress();
	~Own5Bits();
};

