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
	const pxcCHAR* filename; //TODO: forse sarebbe il caso di aggirare questo const
	virtual bool isValidImage(PXCImage* image);
	Mat convertToMat(PXCImage* image);
	std::string WChartToStdString(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale());
	Mat invertMat(Mat toInvert);
	


protected:
	PXCImage::ImageData data;
	PXCImage::ImageInfo info;
	virtual pxcBYTE* computeImage() = 0;


public: 
	ConvertPipeline(const pxcCHAR *filename) : UtilPipeline(Session::getSession(), filename, false)  {
		this->filename = filename;
	}
	void OnImage(PXCImage *image);
	void convert();
	void finalize();


	virtual Size getSize() = 0;
	virtual int getFormatToEncodeTo() = 0;
	virtual string getName() = 0;
	virtual int getSourceFormat() = 0;
	virtual PXCImage::ColorFormat getImageType() = 0;
};

#endif