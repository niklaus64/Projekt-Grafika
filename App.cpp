#include "App.h"

App::App()
{
}

void App::po_nacisnieciu_compress()
{

	switch (1)
	{
	case C_RLE:
		al = new RLE();
		break;
	case C_BYTE_RUN:
		//al = new ByteRun();
		break;
	case C_OWN_5_BITS:
		//al = new Own5Bits();
		break;
	}
	al->compress();
	//al->safe();
}


App::~App()
{
}
