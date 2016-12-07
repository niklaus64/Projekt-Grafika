#pragma once

#include <iostream>
#include <vector>
#include "Enum.h"
#include <fstream>
#include <array>
#include <Windows.h>
#include <list>
#include <bitset>
#include <string>

class DataImage
{
	uint32_t width;
	uint32_t height;
	uint32_t offset;
	compressionType cT;
	

	struct pixel
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;

		bool operator==(pixel &p) const
		{
			if ((r == p.r) && (g == p.g) && (b == p.b)) return true;
			else return false;
		}
	};

	
	
	void FillBitMapFileHeader(BITMAPFILEHEADER &);
	void FillBitMapInfoHeader(BITMAPINFOHEADER &);
public:

	std::vector<pixel> pixmap;
	std::vector<char> bitmap;
	DataImage();
	DataImage(compressionType);
	void WriteDataToSZMIK(std::string);
	void LoadFromBMP(std::string);
	void LoadFromSZMIK(std::string);
	void WriteDataToBMP(std::string);
	compressionType get_cT();
	void GrayScale();
	void brightness(int);
	void contrast(int);
	~DataImage();
};

