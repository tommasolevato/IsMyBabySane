#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

#include <util_render.h>


using namespace std;
using namespace cv;


void ConvertPipeline::OnImage(PXCImage* image) {

	if(isValidImage(image)){
		writer.write(convertToMat(image));
		image->ReleaseAccess(&data);
	}
}

void ConvertPipeline::finalize() {
	writer.release();
}

void ConvertPipeline::convert() {
	Size frameSize = getSize();
	writer.open(WChartToStdString(filename) + getName(), getFormatToEncodeTo(), 30, frameSize, true);
	EnableImage(getImageType());
	LoopFrames();
	finalize();
}

bool ConvertPipeline::isValidImage(PXCImage* image) {
	return (image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR);
}

Mat ConvertPipeline::convertToMat(PXCImage* image) {
	image->QueryInfo(&info);
	
	return Mat(info.height, info.width, getSourceFormat(), computeImage());
}

//TODO: cambiare nome
std::string ConvertPipeline::WChartToStdString( const wchar_t *s, char dfault, const std::locale& loc) {
	std::ostringstream stm;

	while( *s != L'\0' ) {
		stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
	}
	return stm.str();
}
