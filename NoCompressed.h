#pragma once
#include "Algorithm.h"

class NoCompressed : public Algorithm
{
	
public:
	void compress();
	NoCompressed(std::string, int, int, bool);
	~NoCompressed();

	void saveToFile(std::string);
};

