#include "BackgroundCV.h"


BackgroundCV::BackgroundCV() {
	sb = BackgroundSubtractorMOG(5, 3, 0.8);
}

Mat BackgroundCV::findBackground(Mat image) {

	Mat pippo;
	sb(image, pippo, 0.2);
	//sb.setDouble("varThresholdGen", 10);
	//sb.setDouble("backgroundRatio", 1);
	imshow("background", pippo);
	imshow("original", image);
	waitKey(30);
	//getchar();
	return pippo;

}

