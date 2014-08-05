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
	//TODO: prima di fare writer.open() verificare se filename esiste
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
	Mat rawMat(480, 640, getSourceFormat(), frame);
	Mat toReturn = elaborateRawMat(rawMat);
	return toReturn;
}



