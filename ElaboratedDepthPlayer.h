#pragma once


#include "VideoPlayer.h"
#include "MatEncoder.h"

class ElaboratedDepthPlayer : public VideoPlayer {
public:
	ElaboratedDepthPlayer(string filename) : VideoPlayer(filename), filename(filename), depthPlayer(filename) {}
	bool read(Mat& dst);
	void resetRetrieval();


private:
	bool playFrame();
	MatEncoder matEncoder;
	VideoCapture depthPlayer;
	string filename;
};