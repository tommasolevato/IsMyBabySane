#include "DepthPlayer.h"

bool DepthPlayer::playFrame() {
	//TODO: eliminare copia incolla con metodo precedente
	bool success = cap.read(frame);
	if(success) {
		Mat toShow = matEncoder.threeChannels8bitsTo1Channel16Bits(frame);
		//TODO: forse questo smoothing è da togliere
		imshow("", toShow);
		//imwrite("C:/Users/Tommaso/Desktop/frames/" + to_string(frameNumber) + ".png", toShow);
		waitKey(30);
	}
	frameNumber++;
	return success;
}