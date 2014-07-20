#include "RegionSelecter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void RegionSelecter::CallBackFunc(int event, int x, int y, int flags, void* ptr)
{
	if  ( event == CV_EVENT_LBUTTONDOWN )
	{
		cv::Point* p = (cv::Point*)ptr;
		p->x = x;
		p->y = y;
		cout<<x<<" "<<y<<endl;
	}
}

void RegionSelecter::setMaskFromMouse(Mat frame){

	Mat temp;
	frame.copyTo(temp);
	frame.copyTo(originalFrame);

	bool userIsSelecting=true;
	string s="y";

	while(userIsSelecting){
		namedWindow("Select", 1);
		printInstruction();

		Point p;
		setMouseCallback("Select", CallBackFunc,(&p));
		imshow("Select",temp);
		waitKey(0);
		vect.push_back(p);

		if(p.x==0 && p.y==0)
		{
			cout<<"Read better the istruction"<<endl;
			vect.erase(vect.begin()+(vect.size()-1)); //erase the last element of the vector, it is corrupted
		}
		else{
			circle(temp,p,3,Scalar( 0, 0, 255 ),-1,8);
		}

		cout<<"Si intende selezionare altri punti? (y/n)"<<endl;
		cin >> s;
		if(s=="n" && vect.size()>2){
			userIsSelecting=false;
		}
		else{
			if(s=="n" && vect.size()<3){
				cout<<"Non è possibile evidenziare la regione con meno di 3 punti"<<endl;
			}
		}
		destroyAllWindows();
	}
	points[0]=new Point[vect.size()];
	std::copy(vect.begin(),vect.end(),points[0]);
	const Point* pts[1]={const_cast<Point*>(points[0])};

	int npt[] = {vect.size()};
	npoints=npt;

	Mat result=Mat::ones(frame.rows,frame.cols,CV_8U)*255; 
	fillPoly( result, pts, npt, 1, 0, 8 );
	imshow("Mask",result);
	cv::moveWindow("Mask",0,0);
	waitKey(30);
	mask=result;

	subtract(frame,frame,frame,mask);
	imshow("Focus Region",frame);
	cv::moveWindow("Focus Region",650,0);
	waitKey(30);

	setDepthMask();

	cout<<"Is this the region you wanted to evidence?(y/n)"<<endl;
	cin >> s;

	cout<<"Do you want to save the mask?(y/n)"<<endl;
	string str="y";
	cin >> str;
	if(str=="y"){
		string name=string("RGBMask.jpg");
		const char * charName = name.c_str();
		imwrite(charName,mask);

		name=string("DepthMask.jpg");
		charName = name.c_str();
		imwrite(charName,depthMask);
	}
	destroyAllWindows();

	if(s=="n"){
		//FIXME:questo if non funziona ancora
		cout<<"Retry!!"<<endl;
		reset();//TODO: questa c'è da farla!
		setMaskFromMouse(originalFrame);
	}
}

void RegionSelecter::setDepthMask(){

	Point* depthPoints[1];
	depthPoints[0]=new Point[vect.size()];
	std::copy(vect.begin(),vect.end(),depthPoints[0]);
	for (int i=0;i<vect.size();i++){
		depthPoints[0][i].x=std::floor(depthPoints[0][i].x/2);
		depthPoints[0][i].y=std::floor(depthPoints[0][i].y/2);
	}
	const Point* pts[1]={const_cast<Point*>(depthPoints[0])};

	Mat result=Mat::ones(originalFrame.rows/2,originalFrame.cols/2,CV_8U)*255; 
	fillPoly( result, pts, npoints, 1, 0,8);
	depthMask=result;
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
	cvtColor(imread("RGBMask.jpg"),mask,CV_RGB2GRAY);
	cvtColor(imread("DepthMask.jpg"),depthMask,CV_RGB2GRAY);
}

Mat RegionSelecter::getMask(){
	return mask;
}

Mat RegionSelecter::getDepthMask(){
	return depthMask;
}