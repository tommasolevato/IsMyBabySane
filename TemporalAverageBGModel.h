#ifndef TEMPORALAVERAGEBGMODEL_H
#define TEMPORALAVERAGEBGMODEL_H

#include <opencv2\core\core.hpp>
using namespace cv;

class TemporalAverageBGModel{
private:
	double RGBThreshold;
	double RGBAlpha;
	Mat RGBVariance;
	Mat RGBBackground;
	Mat RGBFrame;
	Mat RGBBackgroundMap;
	
	double depthThreshold;
	double depthAlpha;
	Mat depthVariance;
	Mat depthBackground;
	Mat depthFrame;
	Mat depthBackgroundMap;


public:
	TemporalAverageBGModel();
	Mat computeRGBForeground(Mat inputImage);
	Mat computeRGBBackground(Mat inputImage);
	Mat computeDepthForeground(Mat inputImage);
	Mat computeDepthBackground(Mat inputImage);
	void setRGBFirstFrame(Mat inputImage);
};



#endif