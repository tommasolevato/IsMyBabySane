#ifndef INFOPIPELINE_H
#define INFOPIPELINE_H


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include "Session.h"

class InfoPipeline : public UtilPipeline {
public:
	InfoPipeline(const pxcCHAR *file) : UtilPipeline(Session::getSession(), file, false)  {
		numberOfFrames = 0; //TODO: controllare se C++ inizializza a 0 da solo
		isNumberOfFramesInitialized = false;
	}
	void OnImage(PXCImage *image);
	int getTotalNumberOfFrames();


private:
	int numberOfFrames;
	bool isNumberOfFramesInitialized;
};


#endif