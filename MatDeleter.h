#pragma once


#include <opencv2\opencv.hpp>

using namespace cv;

class MatDeleter {
public:
	static void deleteMat(Mat toDelete);
};