#include "DepthPipeline.h"

Size DepthPipeline::getSize() {
	return Size(320, 240);
}

int DepthPipeline::getFormatToEncodeTo() {
	//return CV_FOURCC('P','I','M','1');
	//return CV_FOURCC('X','V','I', 'D');
	//return CV_FOURCC('Y', 'U', 'Y', 'V');
	//return CV_FOURCC('C', 'X', 'Y', '1');
	//return CV_FOURCC('C', 'X', 'Y', '2');
	//return CV_FOURCC('D', 'A', 'V', 'C');
	//return CV_FOURCC('D', 'I', 'V', 'X');
	//return CV_FOURCC('D', 'I', 'V', '3');
	//return CV_FOURCC('M', 'P', '4', '2');
	//return CV_FOURCC('I', '2', '6', '3');
	//return CV_FOURCC('M', 'P', 'E', 'G');
	//return CV_FOURCC('Y', '2', '1', '6');
	//return CV_FOURCC('P', '2', '1', '6');
	return -1;
}

string DepthPipeline::getName() {
	return "_Depth.avi";
}

int DepthPipeline::getSourceFormat() {
	return CV_16UC1;
}

PXCImage::ColorFormat DepthPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_DEPTH;
}