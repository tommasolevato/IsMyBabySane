#include "RegionSelecter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat RegionSelecter::temp;
vector<Point> RegionSelecter::vect;

void RegionSelecter::CallBackFunc(int event, int x, int y, int flags, void* ptr)
{
	if  ( event == CV_EVENT_LBUTTONDOWN )
	{
		cv::Point* p = (cv::Point*)ptr;
		p->x = x;
		p->y = y;
		cout<<x<<" "<<y<<endl;
		circle(temp,*p,3,Scalar( 0, 0, 255 ),-1,8);
		vect.push_back(*p);
		imshow("Select",temp);
	}

}

void RegionSelecter::setMaskFromMouse(Mat frame){
	frame.copyTo(temp);
	frame.copyTo(originalFrame);
	namedWindow("Select", 1);
	printInstruction();
	Point p;
	setMouseCallback("Select", CallBackFunc,(&p));
	imshow("Select",temp);

	while(waitKey(0) != 13) {}

	destroyAllWindows();
	points[0]=new Point[vect.size()];
	
	const Point* pts[1]={const_cast<Point*>(points[0])};
	int npt[] = {(int)vect.size()};
	npoints=npt;

	Mat result = Mat::zeros(480,640,CV_16UC4);;
	if(npoints[0] != 0) {
		std::copy(vect.begin(),vect.end(),points[0]);
		fillPoly( result, pts, npt, 1, Scalar(1,1,1,1), 8 );
	} else {
		vect.clear();
		vect.push_back(Point(0,0));
		vect.push_back(Point(640,0));
		vect.push_back(Point(640, 480));
		vect.push_back(Point(0, 480));
		std::copy(vect.begin(),vect.end(),points[0]);
		int numberOfPoints = 4;
		fillPoly( result, pts, &numberOfPoints, 1, Scalar(1,1,1,1), 8 );
	}

	//cv::moveWindow("Mask",0,0);
	mask=result;

	setDepthMask();

	string name=string("RGBMask.jpg");
	const char * charName = name.c_str();
	imwrite(charName,mask);

	name=string("DepthMask.jpg");
	charName = name.c_str();
	imwrite(charName,depthMask);
	destroyAllWindows();
}

/*else{
if(s=="n" && vect.size()<3){
cout<<"Non è possibile evidenziare la regione con meno di 3 punti"<<endl;
}
}*/







void RegionSelecter::setDepthMask(){
	//Point* depthPoints[1];
	//depthPoints[0]=new Point[vect.size()];
	//std::copy(vect.begin(),vect.end(),depthPoints[0]);
	//for (int i=0;i<vect.size();i++){
	//	depthPoints[0][i].x=std::floor(depthPoints[0][i].x/2);
	//	depthPoints[0][i].y=std::floor(depthPoints[0][i].y/2);
	//}
	//const Point* pts[1]={const_cast<Point*>(depthPoints[0])};

	//Mat result=Mat::ones(originalFrame.rows/2,originalFrame.cols/2,CV_8U)*255; 
	//fillPoly( result, pts, npoints, 1, 0,8);
	depthMask=getMask();
}

void RegionSelecter::printInstruction(){
	cout<<"Follow precisely the instruction:"<<endl;
	cout<<"	1) Select a Poin in the image ('Select' window)"<<endl;
	cout<<"	2) Press 'Enter' "<<endl;
	cout<<"	3) Click on the console"<<endl;
	cout<<"	4) Press continue('y') or stop('n')"<<endl;
	cout<<"	5) Press 'enter'"<<endl;
}

void RegionSelecter::reset(){
	mask.release();
	depthMask.release();
	vect.clear();
	//TODO: questi adrebbero fatti funzionare, credo
	//delete [] points[0];
	//delete [] npoints;
}

//Funzione di utilità, per non stare a risettare la regione ad ogni run
void RegionSelecter::setMaskFromFile(){
	//TODO: ci vorrebbe un controllino sulla validità delle immagini caricate
	//cvtColor(imread("RGBMask.jpg"),mask,CV_RGB2GRAY);
	//cvtColor(imread("DepthMask.jpg"),depthMask,CV_RGB2GRAY);
}

Mat RegionSelecter::getMask(){
	return mask;
}

Mat RegionSelecter::getDepthMask(){
	return depthMask;
}