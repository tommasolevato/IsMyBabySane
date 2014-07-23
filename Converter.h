#ifndef CONVERTER_H
#define CONVERTER_H

#include "RGBPipeline.h"
#include "DepthPipeline.h"
#include "IRPipeline.h"

//TODO: polimorfismo
class Converter {
public:
	Converter(const char* file) : RGBConverter(charPtrToWCharPtr(file)), DepthConverter(charPtrToWCharPtr(file)), IRConverter(charPtrToWCharPtr(file)) {}
	void convert();

private:
	RGBPipeline RGBConverter;
	DepthPipeline DepthConverter;
	IRPipeline IRConverter;
	wchar_t* charPtrToWCharPtr(const char* toConvert);
};


#endif
