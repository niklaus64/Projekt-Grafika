#pragma once
#include "DataImage.h"

class Algorithm
{
protected :
	DataImage *di;
	
public:
	virtual void compress() = 0;
	virtual void saveToFile(std::string) = 0;
	
};

