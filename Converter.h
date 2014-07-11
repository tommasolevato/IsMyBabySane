#ifndef CONVERTER_H
#define CONVERTER_H

#include "RGBPipeline.h"
#include "DepthPipeline.h"

class Converter {
public:
	Converter(const pxcCHAR *file) : RGBConverter(file), DepthConverter(file) {}
	void convert();

private:
	RGBPipeline RGBConverter;
	DepthPipeline DepthConverter;
};


#endif
