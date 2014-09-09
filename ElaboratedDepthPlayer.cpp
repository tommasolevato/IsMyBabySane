#include "ElaboratedDepthPlayer.h"

bool ElaboratedDepthPlayer::playFrame() {
	bool success = read(frame);
	if(success) {
		imshow("", frame);
		waitKey(30);
	}
	frameNumber++;
	return success;
}


bool ElaboratedDepthPlayer::read(Mat& dst) {
	if(depthPlayer.read(dst)) {
		dst = matEncoder.threeChannels8bitsTo1Channel16Bits(dst);
		//TODO: forse questo smoothing è da togliere
		int size = 2;
		Mat element = getStructuringElement(cv::MORPH_RECT,
			cv::Size(2 * size + 1, 2 * size + 1),
			cv::Point(size, size) );

		dilate(dst, dst, element);
		medianBlur(dst, dst, 3);
		return true;
	}
	return false;
}

void ElaboratedDepthPlayer::resetVideo() {
	depthPlayer = VideoCapture(filename);
}