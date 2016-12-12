#include "ByteRun.h"

ByteRun::ByteRun(std::string path, int jasnosc, int kontrast, bool skalaSzarosci)
{
    di = new DataImage(C_BYTE_RUN);
    di->LoadFromBMP(path);
    if (skalaSzarosci) di->GrayScale();
    if (jasnosc != 0)di->brightness(jasnosc);
    if (kontrast != 0)di->contrast(kontrast);
}

ByteRun::~ByteRun()
{
}

void ByteRun::compress(){
    int currentPosition(0);
    int sizePixels = di->getWidth()* di->getHeight();
    std::vector<unsigned char> temp;

    while ((currentPosition < sizePixels)) {

        if ((currentPosition < sizePixels - 1) &&
            (getPixel(currentPosition) == getPixel(currentPosition + 1)))
        {
            int lenghtSek(0);
            while (((currentPosition + lenghtSek) < sizePixels - 1) &&
                (getPixel(currentPosition + lenghtSek) == getPixel(currentPosition + lenghtSek + 1)) &&
                (lenghtSek < 127)) {

                lenghtSek++;
            }
           // cout << -lenghtSek << endl;
            temp.insert(temp.end(), (char)(-lenghtSek));
            temp.insert(temp.end(), (char)getPixel(currentPosition + lenghtSek).b);
            temp.insert(temp.end(), (char)getPixel(currentPosition + lenghtSek).g);
            temp.insert(temp.end(), (char)getPixel(currentPosition + lenghtSek).r);

            currentPosition += lenghtSek + 1;
        }
        else {
            int lengthSek(0);
            while ((currentPosition + lengthSek < sizePixels - 1) &&
                (getPixel(currentPosition + lengthSek) != getPixel(currentPosition + lengthSek + 1)) &&
                (lengthSek < 127))
            {
                lengthSek++;
            }
            temp.insert(temp.end(), (char)lengthSek);
            for (int i(0); i < lengthSek; i++) {
                temp.insert(temp.end(), getPixel(currentPosition + i).b);
                temp.insert(temp.end(), getPixel(currentPosition + i).g);
                temp.insert(temp.end(), getPixel(currentPosition + i).r);
            }
            currentPosition += lengthSek;
        }
       // cout << currentPosition << endl;
    }
    di->bitmap.assign(temp.begin(),temp.end());
    temp.clear();
}

void ByteRun::decompress(DataImage &i){

}

pixel ByteRun::getPixel(int i) {
    pixel temp1;
    uint32_t roznicaSzer =  ((di->getWidth() * 3 + 3) & (~3)) - di->getWidth()*3 ;

    int c = ((i *3) / (di->getWidth()*3) )*roznicaSzer;


    temp1.b = di->bitmap.at(i * 3 + c);
    temp1.g = di->bitmap.at(i * 3 + c +1);
    temp1.r = di->bitmap.at(i * 3 + c + 2);

    return temp1;
}


void ByteRun::saveToFile(std::string path)
{
    di->WriteDataToSZMIK(path);
}
