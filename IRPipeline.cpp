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


void IRPipeline::computeImage() {
	delete frame;
	unsigned __int16* src = (unsigned __int16*)data.planes[1];
	//XXX: brutta l'apparente discrepanza tra pxcBYTE e unsigned __int8
	frame = (pxcBYTE*) malloc (3*info.width*info.height*sizeof(unsigned __int8));

	for(int j=0; j < info.width*info.height; j++) {
		float val = (float)src[j] / 65535;
		val = ( ((val)/(0.016)));
		val = max(val, 0.f);
		val = min(val, 1.f);

		//cout << val << endl;

		frame[3*j] = (unsigned __int8)(val*255);
		frame[(3*j) + 1] = (unsigned __int8)(val*255);
		frame[(3*j) + 2] = (unsigned __int8)(val*255);
	}
	//getchar();
}




//float DEFAULT_SCALE = 30.0f;
//float MAX_Z = 0.5f/13.0f;
//float max_distance = MAX_Z;
//float m_scale = 0.09f*320;
//float range_min = .0f;
//float range_max = max_distance * m_scale / DEFAULT_SCALE;


//for(int j=0; j < 640*480; j++) {
//	frame[3*j] = 0;
//	frame[(3*j)+1] = 0;
//	frame[(3*j)+2] = 0;
//}


//for(int j=0; j < 320*240; j++) {
//	float val = (float)src[j] / 65535;
//	val = 1.f - ( ((val)/(0.015)));
//	val = max(val, 0.f);
//	val = min(val, 1.f);



//	float *uvmap=(float*)data.planes[2];
//		
//	int x = j%320;
//	int y = floor(j/320);
//	int index=((int)y)*320+x;
//	if(uvmap[index*2] > 0 && uvmap[index*2+1] > 0) {
//		float newX = uvmap[(index*2)]*640;
//		float newY = uvmap[(index*2)+1]*480;
//		int index = (int)(3* (( (int)newY*640) + ((int)newX) ));

//		frame[index] = (unsigned __int8)(255*val);
//		frame[index+1] = (unsigned __int8)(255*val);
//		frame[index+2] = (unsigned __int8)(255*val);
//	}
//}