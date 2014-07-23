#ifndef BACKGROUNDCV_H
#define BACKGROUNDCV_H

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;

class BackgroundCV {
public:
	BackgroundCV();
	Mat findBackground(Mat image);


private:
	//Mat seed;
	BackgroundSubtractorMOG sb;

};



#endif