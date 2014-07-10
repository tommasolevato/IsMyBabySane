#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


void ConvertPipeline::OnImage(PXCImage* image) {
	
	PXCImage::ImageData data;
	PXCImage::ImageInfo info;
	
	image->QueryInfo(&info);


	if(isValidImage(image, data))
	{
		cv::Mat result(info.height, info.width, getSourceFormat(), data.planes[0], data.pitches[0]);
		writer << result;
		image->Release();
	}
	else
		cout << "Error getting access to image" << endl;
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

bool ConvertPipeline::isValidImage(PXCImage* image, PXCImage::ImageData data) {
	return image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR;
}