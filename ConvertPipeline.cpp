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
	//TODO: decommentare
	//delete filename;
	//TODO: heap danneggiato (probabilmente deriva da RGBPipeline)
	//delete frame;
}


void ConvertPipeline::OnImage(PXCImage* image) {
	if(isValidImage(image)){
		Mat toWrite = convertToMat(image);
		writer.write(toWrite);
		imshow("Converting", toWrite);
		waitKey(30);
		image->ReleaseAccess(&data);
	}
	frameNumber++;
}

void ConvertPipeline::finalize() {
	writer.release();
}

void ConvertPipeline::convert() {
	Size frameSize = getSize();
	//TODO: al posto di false fare un metodo astratto "colorOrNot"

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
	//FIXME: dimensioni hardcoded
	Mat toReturn(480, 640, getSourceFormat(), frame);
	int size = 2;
	Mat element = getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * size + 1, 2 * size + 1),
		cv::Point(size, size) );
	
	//TODO: decommentare
	//dilate(toReturn, toReturn, element);
	//medianBlur(toReturn, toReturn, 3);
	return toReturn;
}



