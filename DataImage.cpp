#include "DataImage.h"

void DataImage::writeData(const std::string &pathToWrite, compressionType type)
{
	std::fstream file;

	//jeśli ścieżka do zapisu jest pusta
	if (pathToWrite.empty())
		return;

	file.open(pathToWrite, std::ios::out | std::ios::binary);
	
	//blad tworzenia pliku
	if (!file) 
	{
		throw Error(2);
	}

	//zapis nagłówka do pliku w zależności od typu kompresji
	switch (type)
	{
	case C_NOT_COMPRESSED:
		headerBMP(file);
		break;
	case C_RLE:
		headerRLE(file);
		break;
	case C_BYTE_RUN:
		headerByteRun(file);
		break;
	case C_OWN_5_BITS:
		headerSZMIK(file);
		break;
	default:
		break;
	}

	//zapis bitmapy
	if (type == C_NOT_COMPRESSED)
		for (unsigned int i = 0; i < height; i++)
		{
			file.write((char*)bitmap.data() + i*width * 3, width * 3);
			file.write((char*)"0", (((width * 3 + 3) & (~3)) - (width * 3)));
		}
    else 
		for (auto &i : bitmap) file.write((char*)&i, sizeof(i));


	//zamknięcie pliku
	file.close();
}

void DataImage::headerSZMIK(std::fstream &file)
{
	//*************************
	//	//Nagłówke pliku SZMIK:
	//	//	-2 bajty id 'SZ'
	//	//	-4 bajty rodzaj kompresji
    //  //  -1 bajt czy skala szarosci
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	// id
	file << 'S' << 'Z';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));
    file.write((char*)&GrayScale, sizeof(bool));
	
	//szerokość i wysokość
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerRLE(std::fstream &file)
{
    //*************************
    //	//Nagłówke pliku SZMIK:
    //	//	-2 bajty id 'SZ'
    //	//	-4 bajty rodzaj kompresji
    //  //  -1 bajt czy skala szarosci
    //	//	-4 bajty szerokosc
    //	//	-4 bajty wysokosc
    //	//	-8 bajty wilkosc bitmapy
    //****************************

	// id
	file << 'R' << 'L';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));
    file.write((char*)&GrayScale, sizeof(bool));
	
	//szerokość i wysokość
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerByteRun(std::fstream &file)
{
    //*************************
    //	//Nagłówke pliku SZMIK:
    //	//	-2 bajty id 'SZ'
    //	//	-4 bajty rodzaj kompresji
    //  //  -1 bajt czy skala szarosci
    //	//	-4 bajty szerokosc
    //	//	-4 bajty wysokosc
    //	//	-8 bajty wilkosc bitmapy
    //****************************

	// id
	file << 'B' << 'R';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));
    file.write((char*)&GrayScale, sizeof(bool));
	
	//szerokość i wysokość
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerBMP(std::fstream &file)
{
	//*************************
	//	//Nagłówke pliku BMP:
	//	//	-2 bajty id 'BR'
	//	//	-4 bajty rodzaj kompresji
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	FillBitMapFileHeader(fileHeader); //wypelnianie nagłowka BMP
	FillBitMapInfoHeader(infoHeader); //wypelnianie nagłowka bmp

	file.write((char*)&fileHeader, sizeof(fileHeader));
	file.write((char*)&infoHeader, sizeof(infoHeader));
}

void DataImage::loadFile(const std::string &path, bool isCompressed)
{
	std::fstream file;
	
	//jeśli ścieżka do zapisu jest pusta
	if (path.empty())
		return;

	file.open(path, std::ios::in | std::ios::binary);
	
	//blad tworzenia pliku
	if (!file)
	{
		throw Error(1);
	}

	std::vector<char> header;
	
	if (!isCompressed)
	{
		//rozmiar headera gdy plik nie jest skompresowany
		header.resize(54);
		file.read(header.data(), header.size());

		width = *reinterpret_cast<uint32_t *>(&header[18]);
		height = *reinterpret_cast<uint32_t *>(&header[22]);
		offset = *reinterpret_cast<uint32_t*>(&header[10]);
		bitmap.resize(width*height * 3);

		//wczytywanie bitmapy bez zer uzupelniajacych wiersze do wielokrotnosci 4
		for (unsigned int i = 0; i < height; i++)
		{
			file.read((char*)(bitmap.data() + i*width * 3), width * 3);
			file.ignore(((width * 3 + 3) & (~3)) - width * 3);
		}

        for (auto &i : bitmap) {
             i >>= 3;
             i <<= 3;
         }
	}
	else
	{
		//rozmiar headera gdy plik jest skompresowany
        header.resize(23);
		file.read(header.data(), header.size());

		cT = (compressionType) *reinterpret_cast<int*>(&header[2]);
        GrayScale = (bool) *reinterpret_cast<uint8_t*>(&header[6]);
        width = *reinterpret_cast<uint32_t*>(&header[7]);
        height = *reinterpret_cast<uint32_t*>(&header[11]);
        auto dataSize = *reinterpret_cast<size_t*>(&header[15]);
		bitmap.resize(dataSize);

		//normalne wczytywanie bitmapy
		file.read((char*)bitmap.data(), bitmap.size());
	}
	file.close();
}

void DataImage::TransformGrayScale()
{
	for (unsigned int i = 0, suma = 0; i < (width*height * 3); i += 3, suma = 0) 
	{
		suma = (unsigned int)(bitmap[i]) + (unsigned int)(bitmap[i + 1]) + (unsigned int)(bitmap[i + 2]);
		suma /= 3;
		bitmap[i] = (char)suma;
		bitmap[i + 1] = (char)suma;
		bitmap[i + 2] = (char)suma;
	}
    GrayScale=true;
}

void DataImage::TransformBrightness(int brightnessValue)
{

size_t size=bitmap.size();
   for(unsigned int i =0; i<size; i+=3){



        int red = [](int p, int color)->int {
                                            if(color+p<0) return 0;
                                            else if (color+p>=0 && color+p<=255) return p+color;
                                            else return 255;
                    }(brightnessValue,(int)bitmap[i+2]);

        int green = [](int p, int color)->int {
                                            if(color+p<0) return 0;
                                            else if (color+p>=0 && color+p<=255) return p+color;
                                            else return 255;
        }(brightnessValue,(int)bitmap[i+1]);

        int blue = [](int p, int color)->int {
                                        if(color+p<0) return 0;
                                        else if (color+p>=0 && color+p<=255) return p+color;
                                        else return 255;
        }(brightnessValue,(int)bitmap[i]);



        bitmap[i] = (unsigned char)blue;
        bitmap[i+1] = (unsigned char)green;
        bitmap[i+2] = (unsigned char)red;



    }
}

void DataImage::TransformContrast(int contrastValue)
{
    size_t  size = bitmap.size();
 for(unsigned int i =0; i<size; i+=3){
    double a;
    if(contrastValue<=0){
         a=1.0 + (contrastValue/256.0);
    }else{
         a=256.0/pow(2,log2(257-contrastValue));
    }
    int red = [](double p, int color)->int {
                        if((p*(color-(255/2))+(255/2))<0) return 0;
                        else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                        else return 255;
                }(a,(int)bitmap[i+2]);


    int green = [](double p, int color)->int {
                         if((p*(color-(255/2))+(255/2))<0) return 0;
                         else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                         else return 255;
                }(a,(int)bitmap[i+1]);


    int blue = [](double p, int color)->int {
                          if((p*(color-(255/2))+(255/2))<0) return 0;
                          else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                          else return 255;
                }(a,(int)bitmap[i]);

    bitmap[i] = (unsigned char)blue;
    bitmap[i+1] = (unsigned char)green;
    bitmap[i+2] = (unsigned char)red;
 }
}


void DataImage::FillBitMapFileHeader(BITMAPFILEHEADER &fileHeader)
{
    fileHeader.bfType = 'MB';
    fileHeader.bfSize = (size_t)54 + sizeof(bitmap);
	fileHeader.bfOffBits = 54;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;

}

void DataImage::FillBitMapInfoHeader(BITMAPINFOHEADER & infoHeader)
{
	infoHeader.biSize = 40;
	infoHeader.biWidth = width;
	infoHeader.biHeight = height;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 24;
	infoHeader.biCompression = 0;
    infoHeader.biSizeImage = sizeof(bitmap) ;
	infoHeader.biClrUsed = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biClrImportant = 0;

}

uint32_t DataImage::getWidth(){
    return width;
}
uint32_t DataImage::getHeight(){
    return height;
}

bool DataImage::isGrayScale(){
    return GrayScale;
}
