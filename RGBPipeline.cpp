#include "RGBPipeline.h"

Size RGBPipeline::getSize() {
	return Size(640, 480);
}

int RGBPipeline::getFormatToEncodeTo() {
	return CV_FOURCC('X','V','I', 'D');
}

string RGBPipeline::getName() {
<<<<<<< HEAD
	return "_RGB.avi";
=======
	return "1_RGB.avi";
>>>>>>> parent of 3a91e7f... Fix: Memory Leak
}

int RGBPipeline::getSourceFormat() {
	return CV_8UC3;
}

PXCImage::ColorFormat RGBPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_RGB32;
}