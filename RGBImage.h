#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include <opencv2\core\core.hpp>
#include <pxcimage.h>

#include "MyImage.h"

using namespace cv;

class RGBImage: public MyImage{

public:
	RGBImage(){}
	RGBImage(Mat img):MyImage(img){}
	Size getSize() { return Size(640, 480); }
	int getSourceFormat(){return CV_8UC3;}
	PXCImage::ColorFormat getImageType(){return PXCImage::COLOR_FORMAT_RGB32;}
};


#endif