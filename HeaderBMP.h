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
