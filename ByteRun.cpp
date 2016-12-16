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

    if(sizePixels==1){
        temp.insert(temp.end(), (char)(0));
        temp.insert(temp.end(), (char)getPixel(currentPosition).b);
        temp.insert(temp.end(), (char)getPixel(currentPosition).g);
        temp.insert(temp.end(), (char)getPixel(currentPosition).r);
    }else{

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
            temp.insert(temp.end(), (-lenghtSek));
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
            if ((lengthSek + currentPosition == sizePixels - 1) &&
                                (lengthSek < 128)) {
                                lengthSek++;
                            }
            temp.insert(temp.end(), lengthSek-1);
            for (int i(0); i < lengthSek; i++) {
                temp.insert(temp.end(), getPixel(currentPosition + i).b);
                temp.insert(temp.end(), getPixel(currentPosition + i).g);
                temp.insert(temp.end(), getPixel(currentPosition + i).r);
            }
            currentPosition += lengthSek;
        }
       // cout << currentPosition << endl;
    }
    }
    di->bitmap.assign(temp.begin(),temp.end());
    temp.clear();

}

void ByteRun::decompress(DataImage &im){
int i(0);
long long counterBlankBites(0);
uint32_t roznicaSzer = ((im.getWidth() * 3 + 3) & (~3)) - (im.getWidth() * 3);
std::vector <unsigned char> temp;

while(i<im.bitmap.size()){
    if(((char)im.bitmap[i])<0){
     for(int j(0); j<(-((char)im.bitmap[i]-1)); j++){
            temp.push_back(im.bitmap[i+1]);
            temp.push_back(im.bitmap[i+2]);
            temp.push_back(im.bitmap[i+3]);
        }
     i +=4;
    }
    else{
        for(int j(0); j<((char)im.bitmap[i])+1; j++){
         temp.push_back(im.bitmap[i+1+j*3]);
         temp.push_back(im.bitmap[i+2+j*3]);
         temp.push_back(im.bitmap[i+3+j*3]);
         if ((temp.size()-counterBlankBites)%(im.getWidth()*3)==0){
             for(unsigned int i(0); i<roznicaSzer;i++) {temp.push_back(0); counterBlankBites++;}
         }
     }
        i+=(im.bitmap[i]*3)+4;
    }

}

im.bitmap.assign(temp.begin(),temp.end());
temp.clear();
}

pixel ByteRun::getPixel(unsigned int i) {
    pixel temp1;



    temp1.b = di->bitmap.at(i * 3 );
    temp1.g = di->bitmap.at(i * 3 +1);
    temp1.r = di->bitmap.at(i * 3 + 2);

    return temp1;
}


void ByteRun::saveToFile(std::string path)
{
    di->WriteDataToSZMIK(path);
}
