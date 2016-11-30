#pragma once

#include <iostream>
#include <vector>
#include "Enum.h"

class DataImage
{
	uint32_t width;
	uint32_t height;
	uint32_t offset;

	struct pixel
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;

		bool operator==(pixel &p)
		{
			if ((r == p.r) && (g == p.g) && (b = p.b)) return true;
			else return false;
		}
	};

	uint16_t id;

	std::vector<pixel> pixmap;
	std::vector<unsigned char> bitmap;

public:
	DataImage(std::string, compressionType);
	~DataImage();
};

