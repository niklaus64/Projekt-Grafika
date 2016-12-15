#include "DataImage.h"




DataImage::DataImage()
{
}

DataImage::DataImage(compressionType _cT)
{
	cT = _cT;
}

void DataImage::WriteDataToSZMIK(std::string pathToWrite)
{
	std::fstream file;
	file.open(pathToWrite, std::ios::out | std::ios::binary);
	if (!file) {
		std::cout << "Blad przy tworzeniu pliku";
		exit(1);
	}

//*************************
//	//Nag³ówke pliku SZMIK:
//	//	-2 bajty id 'SZ'
//	//	-4 bajty rodzaj kompresji
//	//	-4 bajty szerokosc
//	//	-4 bajty wysokosc
//	//	-8 bajty wilkosc bitmapy
//	//	- duzo bajtow bitmapa
//****************************
  file << 'S' << 'Z';
 file.write((char*)&cT, sizeof(compressionType));
 file.write((char *)&width, sizeof(width));
   file.write((char *)&height, sizeof(height));


    auto s = bitmap.size();

        file.write((char *)&s, sizeof(s));


        for (auto &i : bitmap) file.write((char*)&i,sizeof(i));



	file.close();
}

void DataImage::LoadFromBMP(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in | std::ios::binary);
	if (!file) {
		std::cout << "Blad przy tworzeniu pliku";
		exit(1);
	}

	const size_t HEADER_SIZE = 54;
	std::array<char, HEADER_SIZE> header;

	file.read(header.data(), header.size());
	width = *reinterpret_cast<uint32_t *>(&header[18]);
	height = *reinterpret_cast<uint32_t *>(&header[22]);
	auto file_OffSet = *reinterpret_cast<uint32_t*>(&header[10]);
	
	auto dataSize = ((width * 3 + 3) & (~3)) * height;



		
		bitmap.resize(file_OffSet - HEADER_SIZE);
        file.read((char*)bitmap.data(), bitmap.size());
		bitmap.resize(dataSize);
        file.read((char*)bitmap.data(), bitmap.size());



	
	file.close();
}

void DataImage::LoadFromSZMIK(std::string path)
{
	std::fstream file;
	file.open(path, std::ios::in | std::ios::binary);
	if (!file) {
		std::cout << "Blad przy tworzeniu pliku";
		exit(1);
	}


    const size_t HEADER_SIZE = 22;	//wielkosc nag³owka szmik
	std::array<char, HEADER_SIZE> header;

	file.read(header.data(), header.size());
	cT =(compressionType) *reinterpret_cast<int*>(&header[2]);
	width = *reinterpret_cast<uint32_t*>(&header[6]);
	height = *reinterpret_cast<uint32_t*>(&header[10]);
	auto dataSize = *reinterpret_cast<size_t*>(&header[14]);
	


		bitmap.resize(dataSize);
        file.read((char*)bitmap.data(), bitmap.size());
	
	file.close();
}

void DataImage::WriteDataToBMP(std::string path)
{
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	 
    FillBitMapFileHeader(fileHeader); //wypelnianie nag³owka BMP
	FillBitMapInfoHeader(infoHeader); //wypelnianie nag³owka bmp
	


	std::fstream file;
	file.open(path, std::ios::out | std::ios::binary);
	if (!file) {
		std::cout << "Blad przy tworzeniu pliku";
		exit(1);
	}
	
    file.write((char*)&fileHeader, sizeof(fileHeader));
    file.write((char*)&infoHeader, sizeof(infoHeader));
    file.write((char*)bitmap.data(), bitmap.size());

	file.close();
}

compressionType DataImage::get_cT()
{
	return cT;
}


void DataImage::GrayScale()
{

           for (unsigned int i = 0, suma = 0; i < (width*height * 3); i += 3, suma = 0) {
                suma = (unsigned int)(bitmap[i]) + (unsigned int)(bitmap[i + 1]) + (unsigned int)(bitmap[i + 2]);
                suma /= 3;
                bitmap[i] = (char)suma;
                bitmap[i + 1] = (char)suma;
                bitmap[i + 2] = (char)suma;
            }

}

void DataImage::brightness(int)
{
	//dopisac podobnie jak skala szarosc
}

void DataImage::contrast(int)
{
	//dopisac podobnie jak skala szarosc
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

DataImage::~DataImage()
{

}
