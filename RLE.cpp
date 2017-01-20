#include "RLE.h"


RLE::RLE(std::shared_ptr<DataImage> &data)
{
	di = data;
}

void RLE::compress()
{

    pixel currentPixel;
    pixel comparePixel;
    uint32_t currentPosition = 0;
    std::vector<unsigned char> result;

    if(di->isGrayScale()){
         size_t size = di->bitmap.size();
        for(int i=0; i<size; i+=3){
            result.push_back(di->bitmap[i]);
        }
        di->bitmap.assign(result.begin(),result.end());
        result.clear();
    }

    size_t buffSize = di->bitmap.size() - 1;
    while (currentPosition+2 <= buffSize) {
        currentPixel = pixel(di->bitmap.at(currentPosition), di->bitmap.at(currentPosition + 1), di->bitmap.at(currentPosition + 2));
        unsigned char repeat = 1;
        while (true)
        {
			//gdy wykroczymy poza zakres naszej tablicy
            if (currentPosition + 3 * repeat + 2> buffSize) break;
            //gdy iloœæ powtórzeñ przestaje mieœciæ siê w charze(max zapis 253 - gdy¿ (repeat-2))
			if (repeat >= 255) break;

            comparePixel = pixel(di->bitmap.at(currentPosition + 3 * repeat), di->bitmap.at(currentPosition + 3 * repeat + 1), di->bitmap.at(currentPosition + 3 * repeat + 2));
            if (currentPixel == comparePixel)
            {
               ++repeat;
            }
            else
              break;
        }
        //niezale¿nie od tego czy pixele siê powtarzaj¹ zapisujemy pixel conajmniej raz
		result.push_back(currentPixel.r);
        result.push_back(currentPixel.g);
        result.push_back(currentPixel.b);
		//jeœli pixele siê powtórzy³y
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
			//gdy pixele siê powtarzaj¹ element(currentPosition+6) jest nasz¹ iloœci¹ powtórzeñ
			for (int i = (int)di->bitmap.at(currentPosition + 6) + 2; i > 0; i--)
			{
				result.push_back(currentPixel.r);
				result.push_back(currentPixel.g);
				result.push_back(currentPixel.b);
			}
			//jeœli pixele siê powtórzy³y musimy uwzglêniæ jeden bajt na iloœæ powtórzeñ (st¹d +7 a nie +6)
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

    if(di->isGrayScale()){
        size_t size = di->bitmap.size();
        for(int i=0; i<size; i++){
            result.push_back(di->bitmap[i]);
            result.push_back(di->bitmap[i]);
            result.push_back(di->bitmap[i]);
        }
        di->bitmap.assign(result.begin(),result.end());
        result.clear();
    }
}


RLE::~RLE()
{
	di.reset();
}
