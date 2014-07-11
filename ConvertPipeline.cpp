#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>


using namespace std;
using namespace cv;


void ConvertPipeline::OnImage(PXCImage* image) {
	
	if(isValidImage(image)){
		writer.write(convertToMat(image));
		image->ReleaseAccess(&data);
	}
	else
		cout << "Error getting access to frame" << endl;
}


void ConvertPipeline::finalize() {
	writer.release();
}

void ConvertPipeline::convert() {
	Size frameSize = getSize();
	writer.open("C:/Users/Tommaso/Desktop/" + getName(), getFormatToEncodeTo(), 30, frameSize, true);
	EnableImage(getImageType());
	LoopFrames();
	finalize();
}

bool ConvertPipeline::isValidImage(PXCImage* image) {
	return (image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR);
}

Mat ConvertPipeline::convertToMat(PXCImage* image) {
	PXCImage::ImageInfo info;
	image->QueryInfo(&info);
	return Mat(info.height, info.width, getSourceFormat(), data.planes[0], data.pitches[0]);
}