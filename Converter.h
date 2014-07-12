#ifndef CONVERTER_H
#define CONVERTER_H

#include "RGBPipeline.h"
#include "DepthPipeline.h"

class Converter {
public:
	Converter(const char* file) : RGBConverter(charPtrToWCharPtr(file)), DepthConverter(charPtrToWCharPtr(file)) {}
	void convert();

private:
	RGBPipeline RGBConverter;
	DepthPipeline DepthConverter;
	wchar_t* charPtrToWCharPtr(const char* toConvert);
};


#endif
