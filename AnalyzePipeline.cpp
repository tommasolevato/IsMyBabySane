#include "AnalyzePipeline.h"
#include <pxcprojection.h>
#include <pxcmetadata.h>
#include "BackgroundCV.h"

using namespace std;
using namespace cv;

void AnalyzePipeline::analyze() {
	int frameNumber = 0;
	for(;;) {
		Mat rgbframe;
		Mat depthframe;
		if(!rgbplayer.read(rgbframe) || !depthplayer.read(depthframe)){
			break;
		}

		depthframe = matEncoder.threeChannels8bitsTo1Channel16Bits(depthframe);

		unsigned __int8* rgbData = (unsigned __int8*) rgbframe.data;
		unsigned __int16* depthData = (unsigned __int16*) depthframe.data;

		unsigned __int16* resultData = (unsigned __int16*) malloc (640*480*4*sizeof(unsigned __int16));

		for(int i=0; i < 640*480; i++) {
			resultData[(4*i)]   = (unsigned __int16) rgbData[3*i];
			resultData[(4*i)+1] = (unsigned __int16) rgbData[(3*i)+1];
			resultData[(4*i)+2] = (unsigned __int16) rgbData[(3*i)+2];
			resultData[(4*i)+3] = depthData[i];
		}

		Mat result(480, 640, CV_16UC4, resultData);
		cout << "frame: " << frameNumber << endl;
		frameNumber++;
		bcgRGB.setOriginal(rgbframe);
		bcgRGB.findBackground("", result);

		delete resultData;
	}
}