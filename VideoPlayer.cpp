#include "VideoPlayer.h"
#include "MatDeleter.h"

#include <iostream>

using namespace cv;
using namespace std;

void VideoPlayer::play() {
	frameNumber = 0;
	if ( !player.isOpened() )
		cout << "Cannot open the video file" << endl;

	for(;;) {
		if(!playFrame()) {	
			break;
		}
		MatDeleter::deleteMat(frame);
	}
}

bool VideoPlayer::read(Mat& dst) {
	if(player.read(dst)) {
		elaborate(dst);
		return true;
	}
	return false;
}

void VideoPlayer::playAndSaveFrames() {
	//TODO: non funziona
	frameNumber = 0;
	if ( !player.isOpened() )
		cout << "Cannot open the video file" << endl;

	for(;;) {
		if(!playFrame()) {	
			break;
		}
		//TODO: usare il filename del video (splittato togliendo l'estensione e aggiungendo frameNumber e png)

		//TODO: investigare
		//imwrite("C:/Users/Tommaso/Desktop/frames/" + to_string(frameNumber) + ".png", frame);
	}
}