#ifndef IRPIPELINE_H
#define IRPIPELINE_H

#include "ConvertPipeline.h"

class IRPipeline : public ConvertPipeline {

public: 
	IRPipeline(const pxcCHAR *file) : ConvertPipeline(file) {}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();

private:
	void computeImage();

};

#endif