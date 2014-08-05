#include "OpticalFlow.h"
#include <opencv2\opencv.hpp>

using namespace cv;

OpticalFlow::OpticalFlow(Mat frame){
	frame.copyTo(previousImage);
	int maxCorners=20;//valori a caso
	double qualityLevel=3.0; //valori a caso
	double minDistance=7.0; //valori a caso
	//goodFeaturesToTrack(frame,previousPts, maxCorners, qualityLevel, minDistance, noArray(), 3, true);
}