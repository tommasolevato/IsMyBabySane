#include "BackgroundCV.h"


BackgroundCV::BackgroundCV() {
	sb = BackgroundSubtractorMOG2(5, 0, false);
}

void BackgroundCV::setOriginal(Mat or) {
	this->original = or;

}

Mat BackgroundCV::findBackground(string name, Mat image) {
	Mat foreground;
	sb(image, foreground, 0.5);
	//imshow(name, image);
	imshow(name + " foreground", foreground);
	//cvMoveWindow("foreground", 260, 520);
	//cvMoveWindow("frame", 600, 10);
	waitKey(30);
	return foreground;

}

