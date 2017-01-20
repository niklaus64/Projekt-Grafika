#pragma once
#include <memory>
#include "DataImage.h"


/*	Klasa abstrakcyjna, po której dziedzicz¹ konkretne algorytmy.
	Ka¿da z tych klas posiada metody pozwalaj¹ce na kompresje obrazka
	zapisanego we wskaŸniku inteligentnym di	*/
class Algorithm
{
protected :
	std::shared_ptr<DataImage>		di;
public:
	virtual void					compress() = 0;
	virtual void					decompress() = 0;
};

