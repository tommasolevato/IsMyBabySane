#pragma once


#include <opencv2\core\core.hpp>
using namespace cv;

class OpticalFlow{
public:
	OpticalFlow(Mat frame);
	Mat computeLKOpticalFlow(bool usingPyramid);
	//Mat coputeFarnebackOpticalFlow();



private:
	Mat previousImage;
	Point* previousPts;
	//Mat* previousPyramid;
	//Pyramid parameters
	//Mat img;//8-bit input image.
	////pyramid // output pyramid.
	//Size winSize;// window size of optical flow algorithm. Must be not less than winSize argument of calcOpticalFlowPyrLK(). It is needed to calculate required padding for pyramid levels.
	//int maxLevel;// 0-based maximal pyramid level number.
	//bool withDerivatives;// set to precompute gradients for the every pyramid level. If pyramid is constructed without the gradients then calcOpticalFlowPyrLK() will calculate them internally.
	//int pyrBorder;// the border mode for pyramid layers.
	//int derivBorder;// the border mode for gradients.
	//bool tryReuseInputImage;// put ROI of input image into the pyramid if possible. You can pass false to force dat
};