#ifndef CONVERTPIPELINE_H
#define CONVERTPIPELINE_H


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

private:
	VideoWriter writer;
<<<<<<< HEAD
	PXCImage::ImageData data;
	const pxcCHAR* filename; //TODO: forse sarebbe il caso di aggirare questo const
	
	bool isValidImage(PXCImage* image);
	Mat convertToMat(PXCImage* image);
	std::string WChartToStdString(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale());

=======
	bool isValidImage(PXCImage* image, PXCImage::ImageData data);
>>>>>>> parent of 3a91e7f... Fix: Memory Leak

public: 
	ConvertPipeline(const pxcCHAR *filename) : UtilPipeline(Session::getSession(), filename, false)  {
		this->filename = filename;
	}
	void OnImage(PXCImage *image);
	void convert();
	void finalize();
<<<<<<< HEAD

=======
>>>>>>> parent of 3a91e7f... Fix: Memory Leak

	virtual Size getSize() = 0;
	virtual int getFormatToEncodeTo() = 0;
	virtual string getName() = 0;
	virtual int getSourceFormat() = 0;
	virtual PXCImage::ColorFormat getImageType() = 0;
};

#endif