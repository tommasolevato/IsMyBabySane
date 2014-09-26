#include "BackgroundCV.h"

using namespace std;

BackgroundCV::BackgroundCV() {
	sb = BackgroundSubtractorMOG2(10, 0, false);
	frameNumber = 0;
}

Mat BackgroundCV::findBackground(string name, Mat image) {
	Mat foreground;
	sb(image, foreground, 0.08);
	int size = 1;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * size + 1, 2 * size + 1),
		cv::Point(size, size) );
	morphologyEx(foreground, foreground, CV_MOP_OPEN, element);
	//medianBlur(foreground, foreground, 3);
	imshow(name + " foreground", foreground);
	waitKey(30);
	frameNumber++;
	return foreground;
}

