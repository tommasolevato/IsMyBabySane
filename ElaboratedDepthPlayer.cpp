#include "ElaboratedDepthPlayer.h"

bool ElaboratedDepthPlayer::playFrame() {
	//TODO: eliminare copia incolla con metodo precedente
	bool success = cap.read(frame);
	if(success) {
		Mat toShow = matEncoder.threeChannels8bitsTo1Channel16Bits(frame);
		//TODO: forse questo smoothing è da togliere
		int size = 2;
		Mat element = getStructuringElement(cv::MORPH_RECT,
			cv::Size(2 * size + 1, 2 * size + 1),
			cv::Point(size, size) );

		dilate(toShow, toShow, element);
		medianBlur(toShow, toShow, 3);

		imshow("", toShow);
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

void ElaboratedDepthPlayer::resetRetrieval() {
	depthPlayer = VideoCapture(filename);
}