#include "ConvertPipeline.h"
#include <pxcimage.h>
#include <iostream>
#include "MatDeleter.h"
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include "Util.h"
#include <util_render.h>

using namespace std;
using namespace cv;

ConvertPipeline::~ConvertPipeline() {
	//TODO: decommentare
	//delete filename;
	//TODO: heap danneggiato (probabilmente deriva da RGBPipeline)
	//delete frame;
}

void ConvertPipeline::OnImage(PXCImage* image) {
	if(isValidImage(image)){
		Mat toWrite = convertToMat(image);
		writer.write(toWrite);
		//TODO: far vedere l'immagine di depth originale e non quella a verde e blu
		imshow("Converting", toWrite);
		waitKey(30);
		cleanUp(image, toWrite);
	}
	frameNumber++;
}

void ConvertPipeline::finalize() {
	writer.release();
}

void ConvertPipeline::convert() {
	Size frameSize = getSize();
	//TODO: prima di fare writer.open() verificare se filename esiste
	writer.open(Util::WChartToStdString(filename) + getName(), getFormatToEncodeTo(), 30, frameSize, true);
	EnableImage(getImageType());
	LoopFrames();
	finalize();
}

//TODO: cambiare nome
bool ConvertPipeline::isValidImage(PXCImage* image) {
	return (image->AcquireAccess(PXCImage::ACCESS_READ, &data)>=PXC_STATUS_NO_ERROR);
}

Mat ConvertPipeline::convertToMat(PXCImage* image) {
	image->QueryInfo(&info);
	computeImage();
	//FIXME: dimensioni hardcoded
	Mat rawMat(480, 640, getSourceFormat(), frame);
	//TODO: forse si può evitare questo Template Method
	Mat toReturn = elaborateRawMat(rawMat);
	return toReturn;
}


void ConvertPipeline::cleanUp(PXCImage* originalImage, Mat finalImage) {
	originalImage->ReleaseAccess(&data);
}