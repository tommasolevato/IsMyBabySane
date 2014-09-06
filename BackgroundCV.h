#pragma once


#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;

//TODO: eliminare frameNumber

class BackgroundCV {
public:
	BackgroundCV();
	Mat findBackground(string name, Mat image);
	//TODO: eliminare
	void setOriginal(Mat or);



private:
	int frameNumber;
	BackgroundSubtractorMOG2 sb;
	Mat original;
};