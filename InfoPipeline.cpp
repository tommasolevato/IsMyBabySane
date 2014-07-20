#include "InfoPipeline.h"


void InfoPipeline::OnImage(PXCImage *image) {
	numberOfFrames++;
}

int InfoPipeline::getTotalNumberOfFrames() {
	if(!isNumberOfFramesInitialized) {
		EnableImage(PXCImage::COLOR_FORMAT_RGB32);
		LoopFrames();
		isNumberOfFramesInitialized = true;
	}

	return numberOfFrames;
}