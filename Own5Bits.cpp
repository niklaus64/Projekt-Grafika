#include "Own5Bits.h"


Own5Bits::Own5Bits(DataImage *data)
{
	di = data;
}


Own5Bits::~Own5Bits()
{
	delete di;
}

void Own5Bits::decompress()
{
	const int nbits = 5;
    std::vector<unsigned char>temp;
	temp.push_back('0');

    size_t size = di->bitmap.size();
    for (unsigned int n = nbits - 1, m = 7, j = 0, k = 0; j<size-1; n--, m--) {

		if (di->bitmap[j] & 1 << m) temp[k] |= 1 << n;
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

	di->bitmap.assign(temp.begin(), temp.end());
    temp.clear();
	for (auto &i : di->bitmap) {
		i <<= (8 - nbits);
	}

    if(di->isGrayScale()){
        size=di->bitmap.size();
        for(int i=0; i<size; i++){
            temp.push_back(di->bitmap[i]);
            temp.push_back(di->bitmap[i]);
            temp.push_back(di->bitmap[i]);
        }
        di->bitmap.assign(temp.begin(),temp.end());
        temp.clear();
    }

	
}

void Own5Bits::compress()
{
    const int nbits = 5;
    std::vector<unsigned char> imgCompressed;

    size_t size = di->bitmap.size();


    if(di->isGrayScale()){
        for(int i=0; i<size; i+=3){
            imgCompressed.push_back(di->bitmap[i]);
        }
        di->bitmap.assign(imgCompressed.begin(),imgCompressed.end());
        imgCompressed.clear();
    }


	for (auto &i : di->bitmap) {
		i >>= (8 - nbits);
    }

	imgCompressed.push_back('0');

    size = di->bitmap.size();
    for (unsigned int n = nbits - 1, m = 7, j = 0, k = 0; j<size ; n--, m--) {

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
