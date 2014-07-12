#ifndef DEPTHPIPELINE_H
#define DEPTHPIPELINE_H

#include "ConvertPipeline.h"

class DepthPipeline : public ConvertPipeline {

public: 
	DepthPipeline(const pxcCHAR *file) : ConvertPipeline(file) {}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();


};

#endif