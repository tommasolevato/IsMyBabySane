#include "RGBPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

void RGBPipeline::OnImage(PXCImage *image) {
	
	PXCImage::ImageData data;
	PXCImage::ImageInfo info;
	
	image->QueryInfo(&info);

	//cv::Size size(info.width,info.height);

	if(image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR)
	{
		
		cv::Mat result(info.height, info.width, CV_8UC3, data.planes[0], data.pitches[0]);
		//cv::Mat result(2, 2, 1);
		
		//imshow("", result);
		//cv::waitKey(30);

		writer << result;

		image->Release();
	}
}


void RGBPipeline::finalize() {
	writer.release();
}