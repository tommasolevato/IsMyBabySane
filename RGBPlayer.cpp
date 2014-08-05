#include "RGBPlayer.h"

bool RGBPlayer::playFrame() {
	bool success = cap.read(frame);
	if(success) {
		imshow("", frame);
		waitKey(30);
	}
	frameNumber++;
	return success;
}