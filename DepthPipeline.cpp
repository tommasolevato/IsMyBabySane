#include "DepthPipeline.h"
#include "MatDeleter.h"

Size DepthPipeline::getSize() {
	return Size(640, 480);
}

int DepthPipeline::getFormatToEncodeTo() {
	//return -1;
	//return CV_FOURCC('X', 'V', 'I', 'D');
	//return CV_FOURCC('D', 'I', 'V', '3');
	//return CV_FOURCC('D', 'I', 'V', 'X');
	//return CV_FOURCC('M', 'P', 'E', 'G');
	return CV_FOURCC('L', 'A', 'G', 'S');
}

string DepthPipeline::getName() {
	return "_Depth.avi";
}

int DepthPipeline::getSourceFormat() {
	return CV_16UC1;
}

PXCImage::ColorFormat DepthPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_VERTICES;
}

void DepthPipeline::computeImage() {
	initializeFrame();
	Mat raw(240, 320, getSourceFormat(), temp);
	//medianBlur(raw, raw, 3);
	upscaleFrame();
}

void DepthPipeline::initializeFrame() {
	unsigned __int16* sourceData  = (unsigned __int16*) data.planes[0];
	for(unsigned int j=0; j < info.width*info.height; j++) {
		float correctedPixelValue = correctPixelValue((float) sourceData[j]);
		temp[j]	  = (unsigned __int16) correctedPixelValue;
	}
}

void DepthPipeline::upscaleFrame() {
	float *uvmap=(float*)data.planes[2];
	unsigned __int16* frame16Bits = (unsigned __int16*) frame; 

	for(int j=0; j < getSize().area(); j++) {
		frame16Bits[j] = 0;
	}


	for(unsigned int j=0; j < info.width*info.height; j++) {
		int index = computeUpscaledIndex(j);
		if(index >= 0) {
			frame16Bits[index] = temp[j];
		}
	}
}

int DepthPipeline::computeUpscaledIndex(int originalPixelIndex) {
	float *uvmap=(float*)data.planes[2];
	int x = originalPixelIndex % info.width;
	int y = (int) (originalPixelIndex / info.width);
	int index = ((int)y)*info.width + x;
	if(uvmap[index*2] > 0 && uvmap[index*2+1] > 0) {
		float newX = uvmap[(index*2)] * getSize().width;
		float newY = uvmap[(index*2)+1] * getSize().height;
		int index = (int)((( (int)newY * getSize().width) + ((int)newX) ));
		return index;
	}
	return -1;
}

float DepthPipeline::correctPixelValue(float pixelValue) {
	float normalizedValue = pixelValue / maxPixelValue;
	float invertedAndCorrectedValue = 1.f - (normalizedValue / (float) correctionFactor);
	invertedAndCorrectedValue = max(invertedAndCorrectedValue, 0.f);
	invertedAndCorrectedValue = min(invertedAndCorrectedValue, 1.f);
	invertedAndCorrectedValue *= maxPixelValue;

	return invertedAndCorrectedValue;
}

Mat DepthPipeline::elaborateRawMat(Mat toElaborate) {
	toElaborate = matEncoder.oneChannel16bitsTo3Channels8bits(toElaborate);
	return toElaborate;
}

void DepthPipeline::cleanUp(PXCImage* originalImage, Mat finalImage) {
	originalImage->ReleaseAccess(&data);
	MatDeleter::deleteMat(finalImage);
}