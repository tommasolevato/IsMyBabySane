#pragma once


#include <util_pipeline.h>
#include <opencv2\opencv.hpp>
#include "Session.h"
#include <pxcimage.h>
#include <locale>
#include <sstream>
#include <string>

using namespace cv;
using namespace std;

class ConvertPipeline : public UtilPipeline {
public: 
	ConvertPipeline(const pxcCHAR *filename) : UtilPipeline(Session::getSession(), filename, false)  {
		this->filename = filename;
		frame = (pxcBYTE*) malloc(sizeof(pxcBYTE));
		frameNumber = 0;
	}
	virtual ~ConvertPipeline();
	void OnImage(PXCImage *image);
	void convert();
	void finalize();
	virtual Size getSize() = 0;
	virtual int getFormatToEncodeTo() = 0;
	virtual string getName() = 0;
	virtual int getSourceFormat() = 0;
	virtual PXCImage::ColorFormat getImageType() = 0;



protected:
	PXCImage::ImageData data;
	PXCImage::ImageInfo info;
	//FIXME
	pxcBYTE* frame;
	int frameNumber;
	virtual void computeImage() = 0;
	virtual Mat elaborateRawMat(Mat toElaborate) = 0;
	virtual void cleanUp(PXCImage* originalImage, Mat finalImage);


private:
	VideoWriter writer;
	//TODO: forse sarebbe il caso di aggirare questo const
	const pxcCHAR* filename; 
	virtual bool isValidImage(PXCImage* image);
	Mat convertToMat(PXCImage* image);
};