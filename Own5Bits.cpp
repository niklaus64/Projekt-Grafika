#include "Own5Bits.h"



Own5Bits::Own5Bits(std::string path, int jasnosc, int kontrast, bool skalaSzarosci)
{

	di = new DataImage(C_OWN_5_BITS);
	di->LoadFromBMP(path);
	if (skalaSzarosci) di->GrayScale();
	if (jasnosc != 0)di->brightness(jasnosc);
	if (kontrast != 0)di->contrast(kontrast);
	
	
}


Own5Bits::~Own5Bits()
{
}



void Own5Bits::decompress(DataImage &im)
{
	const int nbits = 5;
	std::vector<char>temp;
	temp.push_back('0');

	for (unsigned int n = nbits - 1, m = 7, j = 0, k = 0; j<im.bitmap.size()-1; n--, m--) {

		if (im.bitmap[j] & 1 << m) temp[k] |= 1 << n;
		else temp[k] &= ~(1 << n);


		if (n == 0) {
			temp.push_back('0');
			n = nbits;
			k++;
		}

		if (m == 0) {
			j++;
			m = 8;
		}
	}

	im.bitmap.assign(temp.begin(), temp.end());
	for (auto &i : im.bitmap) {
		i <<= (8 - nbits);
	}
	
}

void Own5Bits::compress()
{
	const int nbits = 5;
	for (auto &i : di->bitmap) {
		i >>= (8 - nbits);
	}

	std::vector<char> imgCompressed;
	imgCompressed.push_back('0');
	for (unsigned int n = nbits - 1, m = 7, j = 0, k = 0; j<di->bitmap.size() ; n--, m--) {

		if (di->bitmap[j] & 1 << n) imgCompressed[k] |= 1 << m;
		else imgCompressed[k] &= ~(1 << m);


		if (n == 0) {
			n = nbits;
			j++;
		}

		if (m == 0) {
			imgCompressed.push_back('0');
			k++;
			m = 8;
		}
	}

	di->bitmap.assign(imgCompressed.begin(),imgCompressed.end());
	imgCompressed.clear();
}

void Own5Bits::saveToFile(std::string path)
{
	di->WriteDataToSZMIK(path);
}
