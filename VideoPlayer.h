#pragma once

#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace cv;
using namespace std;

class VideoPlayer {
public:
	VideoPlayer(string filename) : cap(filename) {
		//TODO: ripulire
		this->filename = filename;
		frameNumber = 0;
	}
	void play();
	void playAndSaveFrames();

private:
	VideoCapture cap;
	string filename;
	Mat frame;
	int frameNumber;

	bool playFrame();

};