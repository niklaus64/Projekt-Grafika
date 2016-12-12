#pragma once
#include "DataImage.h"

class Algorithm
{
protected :
	DataImage *di;
	
public:
    virtual void compress() = 0;
    virtual void decompress() = 0;
	virtual void saveToFile(const std::string) = 0;
	
};

