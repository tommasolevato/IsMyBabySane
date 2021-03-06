#include "Converter.h"

void Converter::convert() {
	RGBConverter.convert();
	DepthConverter.convert();
}

wchar_t* Converter::charPtrToWCharPtr(const char* toConvert) {
	size_t sizeOfToConvert = strlen(toConvert) + 1;
	wchar_t* toReturn = new wchar_t[sizeOfToConvert];
	mbstowcs (toReturn, toConvert, sizeOfToConvert);
	return toReturn;
}