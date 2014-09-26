#pragma once


#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

//TODO: distruttore virtuale
class VideoPlayer {
public:
	VideoPlayer(string filename) : player(filename) {
		//TODO: ripulire
		this->filename = filename;
		frameNumber = 0;
	}
	virtual ~VideoPlayer() {};	
	void play();
	void playAndSaveFrames();
	virtual bool read(Mat& dst);


protected:
	virtual bool playFrame() = 0;
	VideoCapture player;
	string filename;
	Mat frame;
	int frameNumber;
	virtual void elaborate(Mat& dst) = 0;
};