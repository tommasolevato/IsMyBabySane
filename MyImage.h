#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <opencv2\core\core.hpp>
#include <pxcimage.h>

using namespace cv;

class MyImage{

public:
	MyImage(){}
	MyImage(Mat img);
	virtual Size getSize()=0;
	virtual int getSourceFormat()=0;
	virtual PXCImage::ColorFormat getImageType()=0;

protected:
	Mat image;
};



#endif