#include "AnalyzePipeline.h"
#include <pxcprojection.h>
#include <pxcmetadata.h>
#include "BackgroundCV.h"

using namespace std;
using namespace cv;

void AnalyzePipeline::analyze() {
	int frameNumber = 0;
	for(;;) {
		Mat rgbFrame;
		Mat depthFrame;
		if(!rgbPlayer.read(rgbFrame) || !depthPlayer.read(depthFrame)){
			break;
		}

		if(frameNumber == 0) {
			rs.setMaskFromMouse(rgbFrame);
		}

		//depthFrame = matEncoder.threeChannels8bitsTo1Channel16Bits(depthFrame);

		adjustMatWithBuffer(depthFrame);

		//TODO: eliminare
		//imwrite("C:/Users/Tommaso/Desktop/frames/" + to_string(frameNumber) + ".png", depthFrame);

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
		cout << "frame: " << frameNumber << endl;
		frameNumber++;
		bcgRGB.setOriginal(rgbFrame);
		bcgRGB.findBackground("", result);

		delete resultData;
	}
}



void AnalyzePipeline::updateBuffer(Mat toInsertIntoBuffer) {
	if(buffer.size() == bufferMaxSizeParameter) {
		buffer.pop_front();
	} 

	unsigned __int16* toCopy = (unsigned __int16*)toInsertIntoBuffer.data;
	//TODO: questo è un memoryLeak
	unsigned __int16* toPushData = (unsigned __int16*) malloc(toInsertIntoBuffer.size().area() * sizeof(unsigned __int16));
	for (int i = 0; i < toInsertIntoBuffer.size().area(); i++) {
		toPushData[i] = toCopy[i];
	}
	Mat toPush(toInsertIntoBuffer.rows, toInsertIntoBuffer.cols, CV_16UC1, toPushData);
	buffer.push_back(toInsertIntoBuffer);
	cout << buffer.size() << endl;
}


unsigned __int16 AnalyzePipeline::checkAndAdjustIfIsReasonablyNotBlack(int x, int y) {
	for(std::list<Mat>::iterator it=buffer.end(); it != buffer.begin(); it--) {
			if(it->at<unsigned __int16>(x, y) != 0) {
				return it->at<unsigned __int16>(x, y);
		}
	}
	return 0;
}

//TODO: fare in modo che non consideri i pixel mascherati da RegionSelecter
void AnalyzePipeline::adjustMatWithBuffer(Mat toAdjust) {
	for(int x = 0; x < toAdjust.cols; x++) {
		for(int y = 0; y < toAdjust.rows; y++) {
			unsigned __int16 pixelValue = toAdjust.at<unsigned __int16>(Point(x, y));
			pixelValue = adjustPixelWithBuffer(pixelValue, x, y);
			toAdjust.at<unsigned __int16>(Point(x, y)) = pixelValue;
		}
	}
	updateBuffer(toAdjust);
}

unsigned __int16 AnalyzePipeline::adjustPixelWithBuffer(unsigned __int16 pixelValue, int x, int y) {
	if(buffer.size() == 0) {
		return pixelValue;
	}
	if(pixelValue != 0) {
		unsigned __int16 sum = 0;
		for(std::list<Mat>::iterator it=buffer.begin(); it != buffer.end(); it++) {
			sum += it->at<unsigned __int16>(x, y);
		}
		long reasonablePixelValue = (long) sum / buffer.size();
		//TODO: assicurarsi che non ci siano errori aritmetici
		return (unsigned __int16) reasonablePixelValue;
	}
	return checkAndAdjustIfIsReasonablyNotBlack(x,y);
}


