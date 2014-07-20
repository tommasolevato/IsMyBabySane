#include "TemporalAverageBGModel.h"
#include "AnalysisLib.h"
#include <iostream>
using namespace cv;
using namespace std;

TemporalAverageBGModel::TemporalAverageBGModel(){
	this->RGBThreshold=0.2;
	this->RGBAlpha=0.05;
	this->RGBVariance=Mat::ones(Size(640, 480), CV_8UC3); //TODO: dove eravamo rimasti varianza con 3 canali? allora modificare il controllo della threshold
	this->RGBBackground=Mat::zeros(Size(640, 480), CV_8UC3);
	this->RGBFrame=Mat::zeros(Size(640, 480), CV_8UC3);

	this->depthThreshold=10;
	this->depthAlpha=0.05;
	this->depthVariance=Mat::ones(Size(320, 240), CV_16U);
	this->depthBackground=Mat::ones(Size(320, 240), CV_16U);
	this->depthFrame=Mat::zeros(Size(320, 240), CV_16U);

	this->RGBBackgroundMap=Mat::ones(Size(640, 480), CV_8U)*255;
	this->depthBackgroundMap=Mat::ones(Size(320, 240), CV_8U);
}

Mat TemporalAverageBGModel::computeRGBBackground(Mat inputImage){

	inputImage.copyTo(RGBFrame);
	std::cout<<"Alpha "<<RGBAlpha<<"Threshold "<<RGBThreshold<<std::endl;
	Mat newBackground;
	RGBBackground.copyTo(newBackground);

	Mat op1;
	Mat op2;

	inputImage.copyTo(op1);
	op1=RGBAlpha*op1;
	RGBBackground.copyTo(op2);
	op2=(1-RGBAlpha)*op2;
	add(op1,op2,newBackground,RGBBackgroundMap);
	myImShow(newBackground,"newbackground",0,0);

	Mat newVariance;
	RGBVariance.copyTo(newVariance);
	Mat temp=Mat::zeros(Size(640, 480), CV_8UC3);

	RGBFrame.copyTo(op1);
	RGBBackground.copyTo(op2);
	op2=(-1)*op2;
	add(op1,op2,temp,RGBBackgroundMap);

	pow(temp,2, temp);
	temp.copyTo(op1);
	op1=RGBAlpha*op1;
	RGBVariance.copyTo(op2);
	op2=(1-RGBAlpha)*op2;
	add(op1,op2,newVariance,RGBBackgroundMap);
	myImShow(newVariance,"newVariance", 30,30);

	Mat newBackgroundMap=Mat::ones(Size(640, 480), CV_8U);
	for (int i=0;i<inputImage.rows;i++){
		for (int j=0;j<inputImage.cols;j++){
			double imageRGB [3];
			double backgroundRGB [3];
			for( int k = 0; k < 3; k++){
				int vote=0;
				imageRGB[k]=inputImage.at<Vec3b>(i,j)[k];
				backgroundRGB[k]=newBackground.at<Vec3b>(i,j)[k];
				if( std::abs(imageRGB[k]-backgroundRGB[k]) > RGBThreshold*std::sqrt(newVariance.at<Vec3b>(i,j)[k]))
					vote++;
				if (vote>1)
					newBackgroundMap.at<uchar>(i,j)=0;
				else
					newBackgroundMap.at<uchar>(i,j)=255;
			}
			//TODO: finire distanza colore dal pdf sensors-13-08895-v4.pdf
			//double imageColorNorm=std::pow(imageRGB[0],2)+std::pow(imageRGB[1],2)+std::pow(imageRGB[2],2);
			//double backgroundColorNorm=std::pow(backgroundRGB[0],2)+std::pow(backgroundRGB[1],2)+std::pow(backgroundRGB[2],2);
			//double scalarProd=backgroundRGB[0]*imageRGB[0]+backgroundRGB[1]*imageRGB[1]+backgroundRGB[2]*imageRGB[2];

			//double distance= sqrt( pow((imageRGB[0]-backgroundRGB[0]),2)+
			//					   pow((imageRGB[1]-backgroundRGB[1]),2)+
			//					   pow((imageRGB[2]-backgroundRGB[2]),2) );
			////TODO: la soglia non mi pare normalizzata...
			//if( distance>RGBThreshold*std::sqrt(newVariance.at<Vec3b>(i,j)[0])){
			//	newBackgroundMap.at<uchar>(i,j)=0;
			//}
		}
	}
	myImShow(newBackgroundMap,"newBackgroundMap",60,60);
	newBackground.copyTo(RGBBackground);
	newVariance.copyTo(RGBVariance);
	newBackgroundMap.copyTo(RGBBackgroundMap);

	Mat printableBackground=Mat::zeros(Size(640, 480), CV_8UC3);
	add(RGBBackground,printableBackground,printableBackground,newBackgroundMap);
	return printableBackground;
}

void TemporalAverageBGModel::setRGBFirstFrame(Mat inputImage){
	inputImage.copyTo(RGBBackground);
}