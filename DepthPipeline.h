#ifndef DEPTHPIPELINE_H
#define DEPTHPIPELINE_H

#include "ConvertPipeline.h"

class DepthPipeline : public ConvertPipeline {

public: 
	DepthPipeline(const pxcCHAR *file) : ConvertPipeline(file), maxPixelValue(65535), correctionFactor(0.016) {
		temp = (unsigned __int8*) malloc(3*getSize().area()*sizeof(unsigned __int8));
		frame = (pxcBYTE*) malloc (3*getSize().area()*sizeof(unsigned __int8));
	}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();

private:
	const int maxPixelValue;
	const double correctionFactor;

	//TODO: cambiare nome
	unsigned __int8* temp;



	void computeImage();
	float correctPixelValue(float pixelValue);
	int computeUpscaledIndex(int j);
	void initializeFrame();
	void upscaleFrame();
};

#endif