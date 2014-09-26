#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include "MatDeleter.h"
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include "Util.h"
#include <util_render.h>

using namespace std;
using namespace cv;

ConvertPipeline::~ConvertPipeline() {
}

void ConvertPipeline::OnImage(PXCImage* image) {
	if(isValidImage(image)){
		Mat toWrite = convertToMat(image);
		writer.write(toWrite);
		imshow("Converting", toWrite);
		waitKey(30);
		cleanUp(image, toWrite);
	}
	frameNumber++;
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
	Mat rawMat(480, 640, getSourceFormat(), frame);
	Mat toReturn = elaborateRawMat(rawMat);
	return toReturn;
}


void ConvertPipeline::cleanUp(PXCImage* originalImage, Mat finalImage) {
	originalImage->ReleaseAccess(&data);
}