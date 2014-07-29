#include "DepthPipeline.h"

Size DepthPipeline::getSize() {
	return Size(640, 480);
}

int DepthPipeline::getFormatToEncodeTo() {
	return CV_FOURCC('L', 'A', 'G', 'S');
}

string DepthPipeline::getName() {
	return "_Depth.avi";
}

int DepthPipeline::getSourceFormat() {
	return CV_16UC3;
}

PXCImage::ColorFormat DepthPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_DEPTH;
}


void DepthPipeline::computeImage() {
	unsigned __int16* temp = initializeFrame();
	upscaleFrame(temp);
	delete temp;
}


unsigned __int16* DepthPipeline::initializeFrame() {
	delete frame;
	//TODO: trovare nomi migliori per i prossimi 2
	unsigned __int16* src  = (unsigned __int16*) data.planes[0]; 
	unsigned __int16* temp = (unsigned __int16*) malloc(3*info.width*info.height*sizeof(unsigned __int16));

	for(unsigned int j=0; j < info.width*info.height; j++) {
		float correctedPixelValue = correctPixelValue((float)src[j]);

		temp[3*j]	  = (unsigned __int16) (correctedPixelValue*maxPixelValue);
		temp[(3*j)+1] = (unsigned __int16) (correctedPixelValue*maxPixelValue);
		temp[(3*j)+2] = (unsigned __int16) (correctedPixelValue*maxPixelValue);
	}

	return temp;
}

void DepthPipeline::upscaleFrame(unsigned __int16* frameToUpscale) {
	float *uvmap=(float*)data.planes[2];

	frame = (pxcBYTE*) malloc (3*getSize().area()*sizeof(unsigned __int16));

	for(unsigned int j=0; j < info.width*info.height; j++) {
		int index = computeUpscaledIndex(j);
		if(index >= 0) {
			unsigned __int16* upscaledFrame = (unsigned __int16*)frame;

			upscaledFrame[index]   = frameToUpscale[3*j];
			upscaledFrame[index+1] = frameToUpscale[(3*j)+1];
			upscaledFrame[index+2] = frameToUpscale[(3*j)+2];
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