#pragma once


#include "RegionSelecter.h"
#include "BackgroundCV.h"
#include "Util.h"
#include "MatEncoder.h"

using namespace cv;
using namespace std;

class AnalyzePipeline {
public: 
	AnalyzePipeline(string rgbFile, string depthFile) : rgbplayer(rgbFile), depthplayer(depthFile), frameIstance(0) {}
	void analyze();



private:
	BackgroundCV bcgRGB;
	BackgroundCV bcgDepth;
	VideoCapture rgbplayer;
	VideoCapture depthplayer;
	int frameIstance;
	RegionSelecter rs;
	MatEncoder matEncoder;
};