#include "AnalyzePipeline.h"
#include <pxcprojection.h>
#include <pxcmetadata.h>
#include "BackgroundCV.h"

using namespace std;
using namespace cv;

void AnalyzePipeline::analyze() {
	//TODO: dividere in più metodi
	int frameNumber = 0;
	for(;;) {
		Mat rgbFrame;
		Mat depthFrame;
		if((!rgbPlayer.read(rgbFrame)) || (!depthPlayer.read(depthFrame))){
			break;
		}

		if(frameNumber == 0) {
			rs.setMaskFromMouse(rgbFrame);
		}

		adjustMatWithBuffer(depthFrame);

		//TODO: eliminare
		imwrite("C:/Users/Tommaso/Desktop/frames/" + to_string(frameNumber) + ".png", depthFrame);

		unsigned __int8* rgbData = (unsigned __int8*) rgbFrame.data;
		unsigned __int16* depthData = (unsigned __int16*) depthFrame.data;

		unsigned __int16* resultData = (unsigned __int16*) malloc (640*480*4*sizeof(unsigned __int16));

		for(int i=0; i < 640*480; i++) {
			resultData[(4*i)]   = (unsigned __int16) rgbData[3*i];
			resultData[(4*i)+1] = (unsigned __int16) rgbData[(3*i)+1];
			resultData[(4*i)+2] = (unsigned __int16) rgbData[(3*i)+2];
			resultData[(4*i)+3] = depthData[i];
		}

		Mat result(480, 640, CV_16UC4, resultData);
		multiply(result, rs.getMask(), result);
		cout << "frame: " << frameNumber << "	 buffer: " << buffer.size() << endl;

		frameNumber++;
		bcgRGB.setOriginal(rgbFrame);
		bcgRGB.findBackground("", result);

		delete resultData;
	}
}


Mat AnalyzePipeline::copyDepthMat(Mat toCopy) {
	unsigned __int16* toCopyData = (unsigned __int16*) toCopy.data;
	unsigned __int16* copyData = (unsigned __int16*) malloc(toCopy.size().area() * sizeof(unsigned __int16));

	for(int i=0; i < toCopy.size().area(); i++) {
		copyData[i] = toCopyData[i];
	}
	Mat copy(toCopy.rows, toCopy.cols, CV_16UC1, copyData);
	return copy;
}


void AnalyzePipeline::adjustMatWithBuffer(Mat toAdjust) {

	Mat copy = copyDepthMat(toAdjust);
	eliminateFalseBlacks(copy);
	for(int x = 0; x < copy.cols; x++) {
		for(int y = 0; y < copy.rows; y++) {
			unsigned __int16 pixelValue = copy.at<unsigned __int16>(Point(x, y));
			pixelValue = adjustPixelWithBuffer(pixelValue, x, y);
			toAdjust.at<unsigned __int16>(Point(x, y)) = pixelValue;
			copy.at<unsigned __int16>(Point(x, y)) = pixelValue;
		}
	}
	updateBuffer(copy);
}

void AnalyzePipeline::eliminateFalseBlacks(Mat toAdjust) {
	for(int x = 0; x < toAdjust.cols; x++) {
		for(int y = 0; y < toAdjust.rows; y++) {
			if(toAdjust.at<unsigned __int16>(Point(x, y)) == 0)
				toAdjust.at<unsigned __int16>(Point(x, y)) = checkAndAdjustIfIsReasonablyNotBlack(x, y);
		}
	}

}

unsigned __int16 AnalyzePipeline::adjustPixelWithBuffer(unsigned __int16 pixelValue, int x, int y) {
	int sum = 0;
	int count = 0;
	std::list<Mat>::iterator it=buffer.begin();
	while(it != buffer.end() && count < numberOfFramesForSmoothing)  {
		sum += (it->at<unsigned __int16>(Point(x, y)));
		it++;
		count++;
	}
	sum += pixelValue;
	int numberOfSummedElements = count + 1;
	unsigned __int16 reasonablePixelValue = (unsigned __int16) (sum / numberOfSummedElements);
	return (unsigned __int16) reasonablePixelValue;
}

void AnalyzePipeline::updateBuffer(Mat toInsertIntoBuffer) {
	if(buffer.size() == std::max<int>(numberOfFramesForFalseBlackElimination, numberOfFramesForSmoothing)) {
		Mat toDelete = buffer.front();
		delete toDelete.data;
		buffer.pop_front();
	} 
	buffer.push_back(toInsertIntoBuffer);
}

unsigned __int16 AnalyzePipeline::checkAndAdjustIfIsReasonablyNotBlack(int x, int y) {
	int count = 0;
	std::list<Mat>::reverse_iterator it=buffer.rbegin();
	while(it != buffer.rend() && count < numberOfFramesForFalseBlackElimination) {
		if(it->at<unsigned __int16>(Point(x, y)) != 0) {
			return it->at<unsigned __int16>(Point(x, y));
		}
		count++;
	}
	return 0;
}

//TODO: implemetare
void AnalyzePipeline::averageMatWithBuffer(Mat toAverage) {

}

void AnalyzePipeline::setNumberOfFramesForFalseBlackElimination(int number) {
	numberOfFramesForFalseBlackElimination = number; 
}

void AnalyzePipeline::setNumberOfFramesForSmoothing(int number) {
	numberOfFramesForSmoothing = number;
}