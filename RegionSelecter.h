#pragma once


#include <opencv2\core\core.hpp>
#include <vector>
using namespace cv;

class RegionSelecter{
public:
	RegionSelecter(){}
	void setMaskFromMouse(Mat frame);
	void setMaskFromFile();
	vector<Point> getPoint(){ return vect;}
	static void CallBackFunc(int event, int x, int y, int flags, void* userdata);
	Mat getMask();
	Mat getDepthMask();



private:
	static Mat temp;
	Mat originalFrame;
	Mat mask;
	Mat depthMask;
	Point* points[1];
	int* npoints;
	static std::vector<Point> vect;
	void printInstruction();
	void reset();
	void setDepthMask();
};