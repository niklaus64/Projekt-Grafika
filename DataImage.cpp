#include "DataImage.h"


DataImage::DataImage(compressionType _cT = C_NOT_COMPRESSED) : cT(_cT) {};

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
	//	//	-4 bajty wilkosc bitmapy
	//	//	- duzo bajtow bitmapa
	//****************************

	file << 'S' << 'Z';
	file.write((char*)&cT, sizeof(compressionType));
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	switch (cT) {
	case (C_OWN_5_BITS || C_NOT_COMPRESSED ? C_OWN_5_BITS : C_OWN_5_BITS):
		size_t s = bitmap.size();
		file.write((char*)&s, sizeof(s));
		for (auto &i : bitmap) file.write((char*)&i,sizeof(i));

		//tutaj dopisaæ kolejne case dla innych 
	}

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


	switch (cT) {
	case C_OWN_5_BITS :
		bitmap.resize(file_OffSet - HEADER_SIZE);
		file.read(bitmap.data(), bitmap.size());
		bitmap.resize(dataSize);
		file.read(bitmap.data(), bitmap.size());
		break;
	case C_NOT_COMPRESSED:
		bitmap.resize(file_OffSet - HEADER_SIZE);
		file.read(bitmap.data(), bitmap.size());
		bitmap.resize(dataSize);
		file.read(bitmap.data(), bitmap.size());
		break;
		//tutaj dopisaæ kolejne case dla innych 
	case C_RLE:
		break;
	case C_BYTE_RUN:
		break;
	}

	
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


	const size_t HEADER_SIZE = 18;	//wielkosc nag³owka szmik
	std::array<char, HEADER_SIZE> header;

	file.read(header.data(), header.size());
	cT =(compressionType) *reinterpret_cast<int*>(&header[2]);
	width = *reinterpret_cast<uint32_t*>(&header[6]);
	height = *reinterpret_cast<uint32_t*>(&header[10]);
	auto dataSize = *reinterpret_cast<size_t*>(&header[14]);
	

	switch (cT) {
	case C_OWN_5_BITS:
		bitmap.resize(dataSize);
		file.read(bitmap.data(), bitmap.size());
		break;
	case C_NOT_COMPRESSED:
		bitmap.resize(dataSize);
		file.read(bitmap.data(), bitmap.size());
		break;

		//dopisaæ reszte do innych kompresji
	}
	
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
	file.write(bitmap.data(), bitmap.size());

	file.close();
}

compressionType DataImage::get_cT()
{
	return cT;
}

//skale szarosci dla roznych kompresji niestety :(
//rózne kontenery do przechowywania bitmapy to rozne algorytmy skali szarosci
void DataImage::GrayScale()
{
	switch (cT) {
		case C_OWN_5_BITS:
		for (unsigned int i = 0,suma=0; i < (width*height*3); i += 3, suma = 0) {
			suma = (unsigned int)((uint8_t)(bitmap[i])) + (unsigned int)((uint8_t)(bitmap[i+1])) + (unsigned int)((uint8_t)(bitmap[i+2]));
			suma /= 3;
			bitmap[i] = (char)suma;
			bitmap[i + 1] = (char)suma;
			bitmap[i + 2] = (char)suma;
		}
		break;
		case C_NOT_COMPRESSED:
			for (unsigned int i = 0, suma = 0; i < (width*height * 3); i += 3, suma = 0) {
				suma = (unsigned int)((uint8_t)(bitmap[i])) + (unsigned int)((uint8_t)(bitmap[i + 1])) + (unsigned int)((uint8_t)(bitmap[i + 2]));
				suma /= 3;
				bitmap[i] = (char)suma;
				bitmap[i + 1] = (char)suma;
				bitmap[i + 2] = (char)suma;
			}
			break;

		//tutaj dopisaæ kolejne case dla innych 
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
	fileHeader.bfSize = 54 + (cT == C_OWN_5_BITS || cT == C_NOT_COMPRESSED ? sizeof(bitmap) : sizeof(pixmap));
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
	infoHeader.biSizeImage = (cT==C_OWN_5_BITS || cT==C_NOT_COMPRESSED ? sizeof(bitmap) : sizeof(pixmap));
	infoHeader.biClrUsed = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biClrImportant = 0;
}

DataImage::~DataImage()
{

}
