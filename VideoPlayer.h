#pragma once


#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

//TODO: distruttore virtuale
class VideoPlayer {
public:
	VideoPlayer(string filename) : cap(filename) {
		//TODO: ripulire
		this->filename = filename;
		frameNumber = 0;
	}
	virtual ~VideoPlayer() {};	
	void play();
	void playAndSaveFrames();



protected:
	virtual bool playFrame() = 0;
	VideoCapture cap;
	string filename;
	Mat frame;
	int frameNumber;
};