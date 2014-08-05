#pragma once


#include "VideoPlayer.h"

class RGBPlayer : public VideoPlayer {
public:
	RGBPlayer(string filename) : VideoPlayer(filename) {}



private:
	bool playFrame();
};