#ifndef ANALYZEPIPELINE_H
#define ANALYZEPIPELINE_H


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include <pxcimage.h>
#include <limits>

#include "Session.h"
#include "RGBImage.h"
#include "DepthImage.h"
#include "TemporalAverageBGModel.h"
#include "RegionSelecter.h"
#include "BackgroundGMM.h"

using namespace cv;
using namespace std;

class AnalyzePipeline : public UtilPipeline {

private:
	//FIXME: queste classi alla fine sembrano poco utili
	RGBImage RGBFrame;
	DepthImage depthFrame;

	int frameIstance;
	int firstFrame_;
	int lastFrame_;
	bool checkFrameRange();
	void combinedSpaceAnalysis(Mat rgb,Mat depth);

	//FIXME: chiedere a tommi se vanno bene questi attributi (e cambiare nome)
	TemporalAverageBGModel TABGM;
	RegionSelecter rs;
	BackgroundGMM * RGBbggmm;
	BackgroundGMM * depthbggmm;

	//bool isValidImage(PXCImage* image, PXCImage::ImageData data);

public: 
	AnalyzePipeline(const pxcCHAR *file,int firstFrame=1,int lastFrame=std::numeric_limits<int>::max()) :
		UtilPipeline(Session::getSession(), file, false),firstFrame_(firstFrame),lastFrame_(lastFrame){frameIstance=0;}

	void analyze();
	bool OnNewFrame();
	int getIstance();
};

#endif