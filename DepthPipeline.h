#ifndef DEPTHPIPELINE_H
#define DEPTHPIPELINE_H

#include "ConvertPipeline.h"

class DepthPipeline : public ConvertPipeline {

public: 
	DepthPipeline(const pxcCHAR *file) : ConvertPipeline(file), maxPixelValue(65535), correctionFactor(0.016) {}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();

private:
	const int maxPixelValue;
	const double correctionFactor;
	void computeImage();
	float correctPixelValue(float pixelValue);
	int computeUpscaledIndex(int j);
	unsigned __int16* initializeFrame();
	void upscaleFrame(unsigned __int16* frameToUpscale);
};

#endif