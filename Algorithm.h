#pragma once
#include <memory>
#include "DataImage.h"


/*	Klasa abstrakcyjna, po której dziedziczą konkretne algorytmy.
	Każda z tych klas posiada metody pozwalające na kompresje obrazka
	zapisanego we wskaźniku inteligentnym di	*/
class Algorithm
{
    protected :
    std::shared_ptr<DataImage>		di;
public:
    virtual void					compress() = 0;
    virtual void					decompress() = 0;
};
