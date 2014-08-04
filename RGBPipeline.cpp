#include "RGBPipeline.h"

Size RGBPipeline::getSize() {
	return Size(640, 480);
}

int RGBPipeline::getFormatToEncodeTo() {
	return CV_FOURCC('X','V','I', 'D');
}

string RGBPipeline::getName() {
	return "_RGB.avi";
}

int RGBPipeline::getSourceFormat() {
	return CV_8UC3;
}

PXCImage::ColorFormat RGBPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_RGB32;
}


void RGBPipeline::computeImage() {
	frame =  data.planes[0];
}

Mat RGBPipeline::elaborateRawMat(Mat toElaborate) {
	return toElaborate;
}