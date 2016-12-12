#pragma once
#include "Algorithm.h"

class Own5Bits : public Algorithm
{

public:

	Own5Bits(std::string,int,int,bool);
	~Own5Bits();

    virtual void decompress();
    virtual void compress();
    virtual void saveToFile(std::string);
	
};

