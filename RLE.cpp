#include "RLE.h"


RLE::RLE(DataImage * data)
{
	di = data;
}

void RLE::compress()
{
    size_t buffSize = di->bitmap.size() - 1;
    pixel currentPixel;
    pixel comparePixel;
    uint32_t currentPosition = 0;
    std::vector<unsigned char> result;

    while (currentPosition+2 <= buffSize) {
        currentPixel = pixel(di->bitmap.at(currentPosition), di->bitmap.at(currentPosition + 1), di->bitmap.at(currentPosition + 2));
        unsigned char repeat = 1;
        while (true)
        {
            if (currentPosition + 3 * repeat + 2> buffSize) break;
            if (repeat >= 255) break;

            comparePixel = pixel(di->bitmap.at(currentPosition + 3 * repeat), di->bitmap.at(currentPosition + 3 * repeat + 1), di->bitmap.at(currentPosition + 3 * repeat + 2));
            if (currentPixel == comparePixel)
            {
               ++repeat;
            }
            else
              break;
        }
        result.push_back(currentPixel.r);
        result.push_back(currentPixel.g);
        result.push_back(currentPixel.b);
        if (repeat >= 2)
        {
			result.push_back(currentPixel.r);
			result.push_back(currentPixel.g);
			result.push_back(currentPixel.b);
            result.push_back((unsigned char)(repeat-2));
        }
		currentPosition += 3 * repeat;
      }
      di->bitmap.assign(result.begin(), result.end());
      result.clear();
}

void RLE::decompress()
{
    size_t buffSize = di->bitmap.size() - 1;
	pixel currentPixel;
	pixel comparePixel;
	uint32_t currentPosition = 0;
	std::vector<unsigned char> result;
	while (currentPosition + 5 <= buffSize)
	{
		currentPixel = pixel(di->bitmap.at(currentPosition), di->bitmap.at(currentPosition + 1), di->bitmap.at(currentPosition + 2));
		comparePixel = pixel(di->bitmap.at(currentPosition + 3), di->bitmap.at(currentPosition + 4), di->bitmap.at(currentPosition + 5));
		if (currentPixel == comparePixel)
		{
			for (int i = (int)di->bitmap.at(currentPosition + 6) + 2; i > 0; i--)
			{
				result.push_back(currentPixel.r);
				result.push_back(currentPixel.g);
				result.push_back(currentPixel.b);
			}
			currentPosition += 7;
		}
		else
		{
			result.push_back(currentPixel.r);
			result.push_back(currentPixel.g);
			result.push_back(currentPixel.b);
			currentPosition += 3;
		}
	}
	di->bitmap.assign(result.begin(), result.end());
	result.clear();
}


RLE::~RLE()
{
	delete di;
}