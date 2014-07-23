#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include "Util.h"
#include <util_render.h>


using namespace std;
using namespace cv;


ConvertPipeline::~ConvertPipeline() {
	delete filename;
	//TODO: heap danneggiato (probabilmente deriva da RGBPipeline)
	//delete frame;
}


void ConvertPipeline::OnImage(PXCImage* image) {
	if(isValidImage(image)){
		Mat temp = convertToMat(image);
		writer.write(convertToMat(image));
		image->ReleaseAccess(&data);
	}
}

void ConvertPipeline::finalize() {
	writer.release();
}

void ConvertPipeline::convert() {
	Size frameSize = getSize();
	writer.open(Util::WChartToStdString(filename) + getName(), getFormatToEncodeTo(), 30, frameSize, true);
	EnableImage(getImageType());
	LoopFrames();
	finalize();
}

bool ConvertPipeline::isValidImage(PXCImage* image) {
	return (image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR);
}

Mat ConvertPipeline::convertToMat(PXCImage* image) {
	image->QueryInfo(&info);
	computeImage();
	return Mat(info.height, info.width, getSourceFormat(), frame);
}

//TODO: cambiare nome



