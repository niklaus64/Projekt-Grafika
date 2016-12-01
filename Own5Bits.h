#pragma once
#include "Algorithm.h"

class Own5Bits : public Algorithm
{

public:

	Own5Bits(std::string,int,int,bool);
	~Own5Bits();

	static void decompress(DataImage&);
	void compress();
	void saveToFile(std::string);
	
};

