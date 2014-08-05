#pragma once


#include "VideoPlayer.h"
#include "MatEncoder.h"

class DepthPlayer : public VideoPlayer {
public:
	DepthPlayer(string filename) : VideoPlayer(filename) {}



private:
	bool playFrame();
	MatEncoder matEncoder;
};