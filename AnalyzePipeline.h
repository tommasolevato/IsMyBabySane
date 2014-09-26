#pragma once


#include "RegionSelecter.h"
#include "BackgroundCV.h"
#include "Util.h"
#include "MatEncoder.h"
#include "ElaboratedDepthPlayer.h"
#include "RGBPlayer.h"

using namespace cv;
using namespace std;

class AnalyzePipeline {
public: 
	AnalyzePipeline(string rgbFile, string depthFile) : rgbPlayer(rgbFile), depthPlayer(depthFile), frameIstance(0) {
		numberOfFramesForSmoothing = 5;
		numberOfFramesForFalseBlackElimination = 10;
	}
	void analyze();
	void setNumberOfFramesForSmoothing(int number);
	void setNumberOfFramesForFalseBlackElimination(int number);



private:
	BackgroundCV bcg;
	RGBPlayer rgbPlayer;
	ElaboratedDepthPlayer depthPlayer;
	int frameIstance;
	RegionSelecter rs;
	MatEncoder matEncoder;
	int numberOfFramesForSmoothing;
	int numberOfFramesForFalseBlackElimination;

	list<Mat> buffer;


	void eliminateFalseBlacks(Mat toAdjust);
	void updateBuffer(Mat toInsertIntoBuffer);
	void adjustMatWithBuffer(Mat toAdjust);
	unsigned __int16 checkAndAdjustIfIsReasonablyNotBlack(int x, int y);
	unsigned __int16 adjustPixelWithBuffer(unsigned __int16 pixelValue, int x, int y);
	Mat copyDepthMat(Mat toCopy);
	void averageMatWithBuffer(Mat toAverage);
};