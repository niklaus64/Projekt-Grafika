#pragma once

#include <iostream>
#include <vector>
#include "Enum.h"
#include <fstream>
#include <array>
#include <list>
#include <bitset>

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
    pixel(const unsigned char _r = 0, const unsigned char _g = 0, const unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};

#pragma pack(push,1)
struct BITMAPFILEHEADER{

    unsigned short bfType;
    unsigned int bfSize;
    unsigned int bfOffBits;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
};


struct BITMAPINFOHEADER{
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biYPelsPerMeter;
    int biXPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
};
#pragma pack( pop )

class DataImage
{
	uint32_t width;
	uint32_t height;
	uint32_t offset;
	compressionType cT;
	
	void FillBitMapFileHeader(BITMAPFILEHEADER &);
	void FillBitMapInfoHeader(BITMAPINFOHEADER &);
public:


    std::vector<unsigned char> bitmap;
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

