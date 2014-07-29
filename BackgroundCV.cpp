#include "BackgroundCV.h"


BackgroundCV::BackgroundCV() {
	sb = BackgroundSubtractorMOG(20, 3, 0.1, 3);
}

Mat BackgroundCV::findBackground(Mat image) {
	//buffer di tre frame smoothing
	Mat foreground;
	//medianBlur(image, image, 5);
	//blur(image, image, Size(3,3));
	sb(image, foreground, 0.1);
	//sb.setDouble("varThresholdGen", 10);
	//sb.setDouble("backgroundRatio", 1);
	medianBlur(foreground, foreground, 7);
	imshow("foreground", foreground);
	imshow("original", image);
	waitKey(30);
	//getchar();
	return foreground;

}

