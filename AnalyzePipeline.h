#ifndef ANALYZEPIPELINE_H
#define ANALYZEPIPELINE_H


#include "RegionSelecter.h"
#include "BackgroundCV.h"
#include "Util.h"
#include "MatEncoder.h"

using namespace cv;
using namespace std;

class AnalyzePipeline {

private:
	BackgroundCV bcgRGB;
	BackgroundCV bcgDepth;
	VideoCapture rgbplayer;
	VideoCapture depthplayer;
	int frameIstance;
	RegionSelecter rs;
	MatEncoder matEncoder;

public: 
	/*AnalyzePipeline(string rgbFile, string depthFile) {
		frameIstance=0;
		rgbplayer = VideoCapture(rgbFile);
		depthplayer = VideoCapture(depthFile);
	}

	AnalyzePipeline(wchar_t* rgbFile, wchar_t* depthFile) {
		frameIstance=0;
		rgbplayer = VideoCapture(Util::WChartToStdString(rgbFile));
		depthplayer = VideoCapture(Util::WChartToStdString(depthFile));
	}

	AnalyzePipeline(const char* rgbFile, const char* depthFile) {
		frameIstance=0;
		rgbplayer = VideoCapture(rgbFile);
		depthplayer = VideoCapture(depthFile);
	}*/

	AnalyzePipeline(string rgbFile, string depthFile) : rgbplayer(rgbFile), depthplayer(depthFile), frameIstance(0) {}


	void analyze();
};

#endif