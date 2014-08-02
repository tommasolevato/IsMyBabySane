#include "VideoPlayer.h"

#include <iostream>

using namespace cv;
using namespace std;

void VideoPlayer::play() {
	if ( !cap.isOpened() )  // if not success, exit program
		cout << "Cannot open the video file" << endl;

	for(;;) {
		if(!playFrame()) {	
			break;
		}
	}
}


void VideoPlayer::playAndSaveFrames() {
	if ( !cap.isOpened() )  // if not success, exit program
		cout << "Cannot open the video file" << endl;

	for(;;) {
		if(!playFrame()) {	
			break;
		}
		//TODO: usare il filename del video (splittato togliendo l'estensione e aggiungendo frameNumber e png)
		imwrite("C:/Users/Tommaso/Desktop/frames/" + to_string(frameNumber) + ".png", frame);
	}
}


bool VideoPlayer::playFrame() {
	bool success = cap.read(frame);
	if(success) {
		imshow("", frame);
		waitKey(30);
	}
	frameNumber++;
	return success;
}