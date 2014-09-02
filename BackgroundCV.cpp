#include "BackgroundCV.h"

BackgroundCV::BackgroundCV() {
	sb = BackgroundSubtractorMOG2(10, 0, false);
}

void BackgroundCV::setOriginal(Mat or) {
	this->original = or;
}

Mat BackgroundCV::findBackground(string name, Mat image) {
	Mat foreground;
	sb(image, foreground, 0.08);
	//imshow(name, image);
	int size = 1;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * size + 1, 2 * size + 1),
		cv::Point(size, size) );
	morphologyEx(foreground, foreground, CV_MOP_OPEN, element);
	imshow(name + " foreground", foreground);
	//cvMoveWindow("foreground", 260, 520);
	//cvMoveWindow("frame", 600, 10);
	waitKey(30);
	return foreground;
}

