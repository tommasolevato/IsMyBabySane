#ifndef DEPTHIMAGE_H
#define DEPTHIMAGE_H

#include <opencv2\core\core.hpp>
#include <pxcimage.h>

#include "MyImage.h"

using namespace cv;

class DepthImage: public MyImage{

public:
	DepthImage(){}
	DepthImage(Mat img):MyImage(img){}
	Size getSize() { return Size(320, 240); }
	int getSourceFormat(){return CV_16U;}
	PXCImage::ColorFormat getImageType(){return PXCImage::COLOR_FORMAT_DEPTH;}
};


#endif