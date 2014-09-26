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

void ElaboratedDepthPlayer::resetVideo() {
	depthPlayer = VideoCapture(filename);
}

void ElaboratedDepthPlayer::elaborate(Mat& dst) {
	dst = matEncoder.threeChannels8bitsTo1Channel16Bits(dst);
	int size = 2;
	Mat element = getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * size + 1, 2 * size + 1),
		cv::Point(size, size) );

	dilate(dst, dst, element);
	medianBlur(dst, dst, 3);
}