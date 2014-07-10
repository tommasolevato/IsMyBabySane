#ifndef CONVERTPIPELINE_H
#define CONVERTPIPELINE_H


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include "Session.h"
#include <pxcimage.h>

using namespace cv;
using namespace std;

class ConvertPipeline : public UtilPipeline {

private:
	VideoWriter writer;
	bool isValidImage(PXCImage* image, PXCImage::ImageData data);

public: 
	ConvertPipeline(const pxcCHAR *file) : UtilPipeline(Session::getSession(), file, false)  {}
	void OnImage(PXCImage *image);
	void convert();
	void finalize();

	virtual Size getSize() = 0;
	virtual int getFormatToEncodeTo() = 0;
	virtual string getName() = 0;
	virtual int getSourceFormat() = 0;
	virtual PXCImage::ColorFormat getImageType() = 0;
};

#endif