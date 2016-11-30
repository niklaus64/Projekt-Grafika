#include "App.h"

App::App()
{
}

void App::po_nacisnieciu_compress()
{

	


	switch (0)
	{
	case C_RLE:
		//al = new RLE(); 
		break;
	case C_BYTE_RUN:
		//al = new ByteRun(); 
		break;
	case C_OWN_5_BITS:
		al = new Own5Bits(PATH_TO_FILE_BMP,0,0,false);
		al->compress();
		al->saveToFile(PATH_TO_SAVE_FILE_SZMIK);
		break;
	case C_NOT_COMPRESSED:
		al = new NoCompressed(PATH_TO_FILE_BMP, 0, 0, true);
		al->saveToFile(PATH_TO_SAVE_FILE_BMP);

		break;
	}
	
	
}
//*********************************************
//Niestety w tej metodzie wykorzysta³em metodê z DataImage jako statyczna,
//poniewa¿ nie wiadomo jakiego typu kompresja jest u¿yta
//przy wczytywaniu z pliku SZMIK. Wiecej o tej metodzie (decompres(int)) 
//w pliku DataImage.cpp
//********************************************
void App::poNacisnieciuSave()
{
	DataImage i;
	i.LoadFromSZMIK(PATH_TO_FILE_SZMIK);

	switch (i.get_cT()) {
	case C_OWN_5_BITS:
		Own5Bits::decompress(i);
		
		
	}

	i.WriteDataToBMP(PATH_TO_SAVE_FILE_BMP);
	
}


App::~App()
{
}
