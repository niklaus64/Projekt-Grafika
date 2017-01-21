#pragma once
#include "Algorithm.h"

/*	Algorytm RLE jest bezstratnym algorytmem kompresji.
	Przykład (R,G,B):
	(100,101,102),(100,101,102),(100,101,102) = (100,101,102)(100,101,102)(1)
	^ oszczędność 2 bajtów (przy założeniu że R = G = B = 1Bajt)				*/
class RLE : public Algorithm
{
public:
    RLE(std::shared_ptr<DataImage> &data);
    virtual void compress();
    virtual void decompress();
    ~RLE();
};
