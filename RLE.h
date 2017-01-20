#pragma once
#include "Algorithm.h"

/*	Algorytm RLE jest bezstratnym algorytmem kompresji. 
	Przyk³ad (R,G,B): 
	(100,101,102),(100,101,102),(100,101,102) = (100,101,102)(100,101,102)(1)
	^ oszczêdnoœæ 2 bajtów (przy za³o¿eniu ¿e R = G = B = 1Bajt)				*/
class RLE : public Algorithm
{
public:
	RLE(std::shared_ptr<DataImage> &data);
    virtual void compress();
    virtual void decompress();
    ~RLE();
};

