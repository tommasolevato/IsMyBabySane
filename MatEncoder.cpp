#include "MatEncoder.h"

MatEncoder::MatEncoder() {
	frame8Bits  = (unsigned __int8*)  malloc (sizeof(unsigned __int8));
	frame16Bits = (unsigned __int16*) malloc (sizeof(unsigned __int16));
}


Mat MatEncoder::oneChannel16bitsTo3Channels8bits(Mat toEncode) {
	delete frame8Bits;
	frame8Bits = (unsigned __int8*) malloc (toEncode.size().area()*3*sizeof(unsigned __int8));
	unsigned __int16* sourceData = (unsigned __int16*) toEncode.data;

	for (int i=0; i < toEncode.size().area(); i++) {
		unsigned __int16 pixelValueToEncode = sourceData[i];

		unsigned __int8 mostSignificantBits  = (unsigned __int8) (pixelValueToEncode >> 8);
		unsigned __int8 leastSignificantBits = (unsigned __int8) (pixelValueToEncode);

		frame8Bits[3*i]     = mostSignificantBits;
		frame8Bits[(3*i)+1] = leastSignificantBits;
		frame8Bits[(3*i)+2] = 0;
	}
	return Mat(toEncode.rows, toEncode.cols, CV_8UC3, frame8Bits);
}


Mat MatEncoder::threeChannels8bitsTo1Channel16Bits(Mat toEncode) {
	delete frame16Bits;
	frame16Bits = (unsigned __int16*) malloc (toEncode.size().area()*sizeof(unsigned __int16));
	unsigned __int8* sourceData = (unsigned __int8*) toEncode.data;

	for (int i=0; i < toEncode.size().area(); i++) {
		unsigned __int8 mostSignificantBits  = sourceData[3*i];
		unsigned __int8 leastSignificantBits = sourceData[(3*i)+1];
		
		unsigned __int16 shiftedMostSignificantBits = (unsigned __int16) (mostSignificantBits << 8);
		unsigned __int16 decodedPixelValue = shiftedMostSignificantBits + (unsigned __int16) leastSignificantBits;
		frame16Bits[i] = decodedPixelValue;
	}
	return Mat(toEncode.rows, toEncode.cols, CV_16UC1, frame16Bits);

}

MatEncoder::~MatEncoder() {
	delete frame8Bits;
	delete frame16Bits;
}