#ifndef ANALYSISLIB_H
#define ANALYSISLIB_H

#include <opencv2\core\core.hpp>
using namespace cv;


Mat mykmeans(Mat RGBResult, int numberOfCluster);

Mat normalizeColor(Mat inputImage);

void myImShow(Mat image,string  name, int posX,int posY);

void myFrameWrite(Mat image,int noFrame);

#endif