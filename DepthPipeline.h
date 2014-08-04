#ifndef DEPTHPIPELINE_H
#define DEPTHPIPELINE_H

#include "ConvertPipeline.h"
#include "MatEncoder.h"

class DepthPipeline : public ConvertPipeline {

public: 
	DepthPipeline(const pxcCHAR *file) : ConvertPipeline(file), maxPixelValue(65535), correctionFactor(0.016) {
		temp = (unsigned __int16*) malloc(getSize().area()*sizeof(unsigned __int16));
		frame = (pxcBYTE*) malloc (getSize().area()*sizeof(unsigned __int16));
	}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();

private:
	const int maxPixelValue;
	const double correctionFactor;
	MatEncoder matEncoder;

	//TODO: cambiare nome
	unsigned __int16* temp;

	Mat elaborateRawMat(Mat toElaborate);

	void computeImage();
	float correctPixelValue(float pixelValue);
	int computeUpscaledIndex(int j);
	void initializeFrame();
	void upscaleFrame();
};

#endif