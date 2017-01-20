#pragma once

#pragma pack(push,1)
struct BITMAPFILEHEADER {

	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
};

struct BITMAPINFOHEADER {
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

#include <iostream>
#include <vector>
#include <fstream>
#include "Enum.h"
#include "Error.h"

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

    bool operator !=(pixel &p) const
    {
        if((r!=p.r) || (g!=p.g) || (b!=p.b)) return true;
        else return false;
    }
    pixel(const unsigned char _r = 0, const unsigned char _g = 0, const unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};

class DataImage
{
	uint32_t width;
	uint32_t height;
	uint32_t offset;
    bool GrayScale = false;
	//zapis headerow
	void FillBitMapFileHeader(BITMAPFILEHEADER &);
	void FillBitMapInfoHeader(BITMAPINFOHEADER &);
	void headerSZMIK(std::fstream &);
	void headerRLE(std::fstream &);
	void headerByteRun(std::fstream &);
	void headerBMP(std::fstream &);

public:
	DataImage();

	//vector przechowujacy bitmape obrazu
    std::vector<unsigned char> bitmap;
	
	uint32_t getWidth();
    uint32_t getHeight();
    bool isGrayScale();
	compressionType cT;
	
	void writeData(const std::string &, compressionType);

	//drugi argument true - jesli wczytujemy plik skompresowany (chodzi o wczytywanie header'a i bitmapy)
	void loadFile(const std::string &, bool);

    void TransformGrayScale();
	void brightness(int);
	void contrast(int);
	
	~DataImage();
};

