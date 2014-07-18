#include "DepthPipeline.h"

Size DepthPipeline::getSize() {
	return Size(320, 240);
}

int DepthPipeline::getFormatToEncodeTo() {
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

string DepthPipeline::getName() {
	return "_Depth.avi";
}

int DepthPipeline::getSourceFormat() {
	return CV_8UC3;
}

PXCImage::ColorFormat DepthPipeline::getImageType(){
	return PXCImage::COLOR_FORMAT_DEPTH;
}


pxcBYTE* DepthPipeline::computeImage() {
	unsigned __int16* src = (unsigned __int16*)data.planes[0];
	pxcBYTE* result = (pxcBYTE*) malloc (3*info.width*info.height*sizeof(pxcBYTE));
	
	float DEFAULT_SCALE = 30.0f;
	float MAX_Z = 0.5f/13.0f;
	float max_distance = MAX_Z;
	float m_scale = 0.09f*320;
	float range_min = .0f;
	float range_max = max_distance * m_scale / DEFAULT_SCALE;
	
	for(int j=0; j < info.width*info.height; j++) {
		float val = (float)src[j] / 65535;
		val = 1.f - ((val-range_min)/(range_max-range_min));
		val = max(val, 0.f);
		val = min(val, 1.f);
		//unsigned __int8* rgb = (unsigned __int8*) (&dst[3*j]);

		result[3*j] = (unsigned __int8)(255*val);
		result[(3*j)+1] = (unsigned __int8)(255*val);
		result[(3*j)+2] = (unsigned __int8)(255*val);
	}
	return result;
}