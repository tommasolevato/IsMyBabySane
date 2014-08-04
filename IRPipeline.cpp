#include "IRPipeline.h"

Size IRPipeline::getSize() {
	return Size(320, 240);
}

int IRPipeline::getFormatToEncodeTo() {
	//return CV_FOURCC('P','I','M','1');
	return CV_FOURCC('X','V','I', 'D');
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
	//return -1;
}

string IRPipeline::getName() {
	return "_IR.avi";
}

int IRPipeline::getSourceFormat() {
	return CV_8UC3;
}

PXCImage::ColorFormat IRPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_DEPTH;
}

//TODO: aggiustare e togliere gli eventuali copia-incolla con DepthPipeline
void IRPipeline::computeImage() {
	delete frame;
	unsigned __int16* src = (unsigned __int16*)data.planes[1];
	//XXX: brutta l'apparente discrepanza tra pxcBYTE e unsigned __int8
	frame = (pxcBYTE*) malloc (3*info.width*info.height*sizeof(unsigned __int8));

	for(unsigned int j=0; j < info.width*info.height; j++) {
		float val = (float)src[j] / 65535;
		val = (float)( ((val)/(0.016)));
		val = max(val, 0.f);
		val = min(val, 1.f);

		//cout << val << endl;

		frame[3*j] = (unsigned __int8)(val*255);
		frame[(3*j) + 1] = (unsigned __int8)(val*255);
		frame[(3*j) + 2] = (unsigned __int8)(val*255);
	}
	//getchar();
}

Mat IRPipeline::elaborateRawMat(Mat toElaborate) {
	return toElaborate;

}