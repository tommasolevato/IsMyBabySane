#include "AnalysisLib.h"

#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

Mat mykmeans(Mat RGBResult, int numberOfCluster){
	Mat labels; 
	TermCriteria criteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001);
	Mat samples(RGBResult.rows * RGBResult.cols, 3, CV_32F);
	Mat centers;
	for( int y = 0; y < RGBResult.rows; y++ ){
		for( int x = 0; x < RGBResult.cols; x++ ){
			for( int z = 0; z < 3; z++){
				samples.at<float>(y + x*RGBResult.rows, z)=RGBResult.at<Vec3b>(y,x)[z];
			}
		}
	}

	kmeans(samples, numberOfCluster, labels, criteria, 1, KMEANS_PP_CENTERS, centers);

	Mat new_image( RGBResult.size(), RGBResult.type() );
	for( int y = 0; y < RGBResult.rows; y++ ){
		for( int x = 0; x < RGBResult.cols; x++ ){ 
			int cluster_idx = labels.at<int>(y + x*RGBResult.rows,0);
			new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
			new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
			new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
		}
	}
	return new_image;
}

Mat normalizeColor(Mat inputImage){
	Mat normalizedImage;
	inputImage.copyTo(normalizedImage);
	for( int y = 0; y < inputImage.rows; y++ ){
		for( int x = 0; x < inputImage.cols; x++ ){
			//questi potrebbero essere in ordine diverso
			double red= inputImage.at<Vec3b>(y,x)[0];
			double green= inputImage.at<Vec3b>(y,x)[1];
			double blu= inputImage.at<Vec3b>(y,x)[2];
			double sum=red+green+blu;
			normalizedImage.at<Vec3b>(y,x)[0] = (red*256)/sum;
			normalizedImage.at<Vec3b>(y,x)[1] = (green*256)/sum;
			normalizedImage.at<Vec3b>(y,x)[2] = (blu*256)/sum;
		}
	}
	return normalizedImage;
}

void myImShow(Mat image,string  name,int posX,int posY){
	imshow(name, image);
	cv::waitKey(30);
	cv::moveWindow(name,posX,posY);
	getchar();
}
void myFrameWrite(Mat image,int noFrame){
	string name=string("frame3/image")+to_string(noFrame)+string(".jpg");
	const char * charName = name.c_str();
	imwrite(charName,image);
}