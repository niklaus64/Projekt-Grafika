#include "DataImage.h"


DataImage::DataImage() { }

void DataImage::writeData(const std::string &pathToWrite, compressionType type)
{
	std::fstream file;
    if (pathToWrite.empty())
		throw Error(1);
	file.open(pathToWrite, std::ios::out | std::ios::binary);
	if (!file) {
		//blad tworzenia pliku
		throw Error(1);
	}

	//zapis nag³ówka do pliku w zale¿noœci od typu kompresji
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
	{
		for (unsigned int i = 0; i < height; i++)
		{
			file.write((char*)bitmap.data() + i*width * 3, width * 3);
			file.write((char*)"0", (((width * 3 + 3) & (~3)) - (width * 3)));
		}
	}
	else
	for (auto &i : bitmap) file.write((char*)&i, sizeof(i));

	//zamkniêcie pliku
	file.close();
}

void DataImage::headerSZMIK(std::fstream &file)
{
	//*************************
	//	//Nag³ówke pliku SZMIK:
	//	//	-2 bajty id 'SZ'
	//	//	-4 bajty rodzaj kompresji
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	// id
	file << 'S' << 'Z';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));

	//szerokoœæ i wysokoœæ
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerRLE(std::fstream &file)
{
	//*************************
	//	//Nag³ówke pliku RLE:
	//	//	-2 bajty id 'RL'
	//	//	-4 bajty rodzaj kompresji
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	// id
	file << 'R' << 'L';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));

	//szerokoœæ i wysokoœæ
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerByteRun(std::fstream &file)
{
	//*************************
	//	//Nag³ówke pliku Byte Run:
	//	//	-2 bajty id 'BR'
	//	//	-4 bajty rodzaj kompresji
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	// id
	file << 'B' << 'R';

	//rodzaj kompresji
	file.write((char*)&cT, sizeof(compressionType));

	//szerokoœæ i wysokoœæ
	file.write((char *)&width, sizeof(width));
	file.write((char *)&height, sizeof(height));

	//rozmiar bitmapy
	auto s = bitmap.size();
	file.write((char *)&s, sizeof(s));
}

void DataImage::headerBMP(std::fstream &file)
{
	//*************************
	//	//Nag³ówke pliku BMP:
	//	//	-2 bajty id 'BR'
	//	//	-4 bajty rodzaj kompresji
	//	//	-4 bajty szerokosc
	//	//	-4 bajty wysokosc
	//	//	-8 bajty wilkosc bitmapy
	//****************************

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	FillBitMapFileHeader(fileHeader); //wypelnianie nag³owka BMP
	FillBitMapInfoHeader(infoHeader); //wypelnianie nag³owka bmp

	file.write((char*)&fileHeader, sizeof(fileHeader));
	file.write((char*)&infoHeader, sizeof(infoHeader));
}

void DataImage::loadFile(const std::string &path, bool isCompressed)
{
	std::fstream file;
	file.open(path, std::ios::in | std::ios::binary);
	if (!file) {
		throw(Error(1));
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
		header.resize(22);
		file.read(header.data(), header.size());

		cT = (compressionType) *reinterpret_cast<int*>(&header[2]);
		width = *reinterpret_cast<uint32_t*>(&header[6]);
		height = *reinterpret_cast<uint32_t*>(&header[10]);
		auto dataSize = *reinterpret_cast<size_t*>(&header[14]);
		bitmap.resize(dataSize);

		//normalne wczytywanie bitmapy
		file.read((char*)bitmap.data(), bitmap.size());
	}


	file.close();
}


void DataImage::GrayScale()
{
	for (unsigned int i = 0, suma = 0; i < (width*height * 3); i += 3, suma = 0) 
	{
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

DataImage::~DataImage() { }
