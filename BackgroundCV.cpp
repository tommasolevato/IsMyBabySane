#include "BackgroundCV.h"


BackgroundCV::BackgroundCV() {
	sb1 = BackgroundSubtractorMOG2();
	sb2 = BackgroundSubtractorMOG2();
}

void BackgroundCV::setOriginal(Mat or) {
	this->original = or;

}

Mat BackgroundCV::findBackground(Mat image) {
	//buffer di tre frame smoothing
	Mat foreground;
	Mat foregroundOnlyRGB;
	//medianBlur(image, image, 5);
	//blur(image, image, Size(3,3));
	sb1(image, foreground, 0.1);
	sb2(original, foregroundOnlyRGB, 0.1);
	//sb.setDouble("varThresholdGen", 10);
	//sb.setDouble("backgroundRatio", 1);
	
	//medianBlur(foreground, foreground, 3);
	//medianBlur(foregroundOnlyRGB, foregroundOnlyRGB, 3);
	//imshow("frame", image);
	imshow("foreground", foreground);
	imshow("foreground with only RGB", foregroundOnlyRGB);
	cvMoveWindow("foreground", 260, 520);
	cvMoveWindow("foreground with only RGB", 945, 520);
	cvMoveWindow("frame", 600, 10);
	//imshow("RGB + Depth image", image);
	waitKey(30);
	getchar();
	//waitKey(30);
	//waitKey(30);
	
	return foreground;

}

