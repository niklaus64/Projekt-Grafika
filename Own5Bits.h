#pragma once
#include "Algorithm.h"


class Own5Bits : public Algorithm
{
public:
	Own5Bits(std::shared_ptr<DataImage> &data);
	virtual void compress();
	virtual void decompress();
	~Own5Bits();
};

