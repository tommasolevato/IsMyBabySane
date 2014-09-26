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