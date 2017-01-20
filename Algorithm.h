#pragma once
#include <memory>
#include "DataImage.h"


/*	Klasa abstrakcyjna, po kt�rej dziedzicz� konkretne algorytmy.
	Ka�da z tych klas posiada metody pozwalaj�ce na kompresje obrazka
	zapisanego we wska�niku inteligentnym di	*/
class Algorithm
{
protected :
	std::shared_ptr<DataImage>		di;
public:
	virtual void					compress() = 0;
	virtual void					decompress() = 0;
};

