#ifndef RGBPIPELINE_H
#define RGBPIPELINE_H


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include "ConvertPipeline.h"

using namespace cv;
using namespace std;

class RGBPipeline : public ConvertPipeline {

public: 
	RGBPipeline(const pxcCHAR *file) : ConvertPipeline(file) {}

	Size getSize();
	int getFormatToEncodeTo();
	string getName();
	int getSourceFormat();
	PXCImage::ColorFormat getImageType();


};

#endif