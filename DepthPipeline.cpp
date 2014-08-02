#include "DepthPipeline.h"

Size DepthPipeline::getSize() {
	return Size(640, 480);
}

int DepthPipeline::getFormatToEncodeTo() {
	return CV_FOURCC('X', 'V', 'I', 'D');
}

string DepthPipeline::getName() {
	return "_Depth.avi";
}

int DepthPipeline::getSourceFormat() {
	return CV_8UC3;
}

PXCImage::ColorFormat DepthPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_DEPTH;
}


void DepthPipeline::computeImage() {
	initializeFrame();
	upscaleFrame();
	
	//TODO: decommentare
	//delete temp;
}


void DepthPipeline::initializeFrame() {
	//TODO: decommentare
	//delete frame;
	//TODO: trovare nomi migliori per i prossimi 2
	unsigned __int16* src  = (unsigned __int16*) data.planes[0];
	//temp = (unsigned __int8*) malloc(3*info.width*info.height*sizeof(unsigned __int8));
	for(unsigned int j=0; j < info.width*info.height; j++) {
		float correctedPixelValue = correctPixelValue((float)src[j]);

		unsigned __int16 valueToEncode = (unsigned __int16) (correctedPixelValue*maxPixelValue);

		unsigned __int8 mostSignificantBits = (unsigned __int8) (valueToEncode >> 8);

		temp[3*j]	  = mostSignificantBits;
		temp[(3*j)+1] = (unsigned __int8) valueToEncode;
		temp[(3*j)+2] = 0;
	}
}

void DepthPipeline::upscaleFrame() {
	float *uvmap=(float*)data.planes[2];

	//frame = (pxcBYTE*) malloc (3*getSize().area()*sizeof(unsigned __int8));

	for(unsigned int j=0; j < 3*getSize().area(); j++) {

		frame[j] = 0;

	}


	for(unsigned int j=0; j < info.width*info.height; j++) {
		int index = computeUpscaledIndex(j);
		if(index >= 0) {
			frame[index]   = temp[3*j];
			frame[index+1] = temp[(3*j)+1];
			frame[index+2] = temp[(3*j)+2];
		}
	}
}


int DepthPipeline::computeUpscaledIndex(int originalPixelIndex) {
	float *uvmap=(float*)data.planes[2];
	int x = originalPixelIndex % info.width;
	int y = (int)(originalPixelIndex / info.width);
	int index=((int)y)*info.width + x;
	if(uvmap[index*2] > 0 && uvmap[index*2+1] > 0) {
		float newX = uvmap[(index*2)] * getSize().width;
		float newY = uvmap[(index*2)+1] * getSize().height;
		int index = (int)(3* (( (int)newY * getSize().width) + ((int)newX) ));
		return index;
	}
	return -1;
}


float DepthPipeline::correctPixelValue(float pixelValue) {
	float normalizedValue = pixelValue / maxPixelValue;
	float invertedAndCorrectedValue = 1.f - (normalizedValue / (float)correctionFactor);
	invertedAndCorrectedValue = max(invertedAndCorrectedValue, 0.f);
	invertedAndCorrectedValue = min(invertedAndCorrectedValue, 1.f);

	//TODO: trovare un nome più appropriato
	return invertedAndCorrectedValue;
}