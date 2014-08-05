#pragma once


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