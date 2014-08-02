#ifndef BACKGROUNDCV_H
#define BACKGROUNDCV_H

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;

class BackgroundCV {
public:
	BackgroundCV();
	Mat findBackground(string name, Mat image);
	//TODO: eliminare
	void setOriginal(Mat or);

private:
	BackgroundSubtractorMOG2 sb;
	Mat original;

};



#endif