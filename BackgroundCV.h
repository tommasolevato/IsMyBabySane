#pragma once


#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;

class BackgroundCV {
public:
	BackgroundCV();
	Mat findBackground(string name, Mat image);



private:
	int frameNumber;
	BackgroundSubtractorMOG2 sb;
	Mat original;
};