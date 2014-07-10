#ifndef CONVERTPIPELINE_H
#define CONVERTPIPELINE_H


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include "Session.h"

using namespace cv;
using namespace std;

class ConvertPipeline : public UtilPipeline {

private:
	VideoWriter writer;
	bool isValidImage(PXCImage* image, PXCImage::ImageData data);

public: 
	ConvertPipeline(const pxcCHAR *file) : UtilPipeline(Session::getSession(), file, false)  {
		Size s(640, 480);
		writer.open("C:/Users/Tommaso/Desktop/1.avi", CV_FOURCC('X','V','I', 'D'), 30, s, true);
	}
	void OnImage(PXCImage *image);
	void convert();
	void finalize();
};

#endif