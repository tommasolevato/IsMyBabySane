#ifndef CONVERTER_H
#define CONVERTER_H

#include "RGBPipeline.h"


class Converter {
public:
<<<<<<< HEAD
	Converter(const char* file) : RGBConverter(charPtrToWCharPtr(file)), DepthConverter(charPtrToWCharPtr(file)) {}
=======
	Converter(const pxcCHAR *file) : RGBConverter(file) {}
>>>>>>> parent of 3a91e7f... Fix: Memory Leak
	void convert();

private:
	RGBPipeline RGBConverter;
<<<<<<< HEAD
	DepthPipeline DepthConverter;
	wchar_t* charPtrToWCharPtr(const char* toConvert);
=======
>>>>>>> parent of 3a91e7f... Fix: Memory Leak
};


#endif
