#pragma once
#include "RLE.h"
#include "Enum.h"

class App
{
	compressionType cT;
	Algorithm *al;
public:
	App();
	void po_nacisnieciu_compress();
	~App();
};
