#include "RLE.h"

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

void RLE::decompress(DataImage &im)
{
    size_t buffSize = im.bitmap.size() - 1;
       pixel currentPixel;
       pixel comparePixel;
       uint32_t currentPosition = 0;
       std::vector<unsigned char> result;
       while (currentPosition + 5 <= buffSize)
       {

           currentPixel = pixel(im.bitmap.at(currentPosition), im.bitmap.at(currentPosition + 1), im.bitmap.at(currentPosition + 2));
           comparePixel = pixel(im.bitmap.at(currentPosition + 3), im.bitmap.at(currentPosition + 4), im.bitmap.at(currentPosition + 5));
           if (currentPixel == comparePixel)
           {
               for (int i = (int)im.bitmap.at(currentPosition + 6) + 2; i > 0; i--)
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
       im.bitmap.assign(result.begin(), result.end());
       result.clear();
}

void RLE::saveToFile(const std::string path)
{
    di->WriteDataToSZMIK(path);
}

RLE::RLE(std::string path, int brightness, int contrast, bool greyScale)
{
    di = new DataImage(C_RLE);
    di->LoadFromBMP(path);
    if (greyScale) di->GrayScale();
    if (brightness != 0) di->brightness(brightness);
    if (contrast != 0) di->contrast(contrast);
}


RLE::~RLE()
{
}
