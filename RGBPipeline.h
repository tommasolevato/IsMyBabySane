#ifndef RGBPIPELINE_H
#define RGBPIPELINE_H

#include "ConvertPipeline.h"

class RGBPipeline : public ConvertPipeline {

public: 
	RGBPipeline(const pxcCHAR *file) : ConvertPipeline(file) {}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();

private:
	void computeImage();
	Mat elaborateRawMat(Mat toElaborate);
};

#endif