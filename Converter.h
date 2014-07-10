#ifndef CONVERTER_H
#define CONVERTER_H

#include "RGBPipeline.h"


class Converter {
public:
	Converter(const pxcCHAR *file) : RGBConverter(file) {}
	void convert();

private:
	RGBPipeline RGBConverter;
};


#endif
