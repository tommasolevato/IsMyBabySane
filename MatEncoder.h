#pragma once

#include <opencv2\opencv.hpp>

using namespace cv;

class MatEncoder {

public:
	MatEncoder();
	~MatEncoder();

	Mat oneChannel16bitsTo3Channels8bits(Mat toEncode);
	Mat threeChannels8bitsTo1Channel16Bits(Mat toEncode);
	
	
private:
	unsigned __int8*  frame8Bits;
	unsigned __int16* frame16Bits;

};