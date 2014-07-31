#ifndef BACKGROUNDCV_H
#define BACKGROUNDCV_H

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace cv;

class BackgroundCV {
public:
	BackgroundCV();
	Mat findBackground(Mat image);
	//TODO: eliminare
	void setOriginal(Mat or);

private:
	//Mat seed;

	//FIXME: ce ne vorr� solo uno in futuro
	BackgroundSubtractorMOG2 sb1;
	BackgroundSubtractorMOG2 sb2;
	Mat original;

};



#endif