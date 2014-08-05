#include "DepthPlayer.h"
#include "RegionSelecter.h"

bool DepthPlayer::playFrame() {
	//TODO: eliminare copia incolla con metodo precedente
	bool success = cap.read(frame);
	if(success) {
		Mat toShow = matEncoder.threeChannels8bitsTo1Channel16Bits(frame);
		//TODO: forse questo smoothing è da togliere
		medianBlur(toShow, toShow, 3);
		imshow("", toShow);
		waitKey(30);
	}
	frameNumber++;
	return success;
}