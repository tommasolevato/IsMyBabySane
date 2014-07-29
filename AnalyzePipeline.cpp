#include "AnalyzePipeline.h"
#include <pxcprojection.h>
#include <pxcmetadata.h>
#include "BackgroundCV.h"

using namespace std;
using namespace cv;

Mat completeConvertDepthToRGB(Mat depthImage, PXCImage::ImageData pxcDepthImageData);
Mat naiveConvertDepthToGray(Mat depthImage);
pxcBYTE* computeDepthImage(	PXCImage::ImageData depthData,PXCImage::ImageInfo depthInfo);


bool AnalyzePipeline::checkFrameRange(){
	return (frameIstance>firstFrame_&&frameIstance<lastFrame_);
}


bool AnalyzePipeline::OnNewFrame() {
	//frameIstance++;
	cout<<"\r"<<"               \r"<<frameIstance<<"    ";



	PXCImage *color_image=QueryImage(PXCImage::IMAGE_TYPE_COLOR);
	PXCImage *depth_image=QueryImage(PXCImage::IMAGE_TYPE_DEPTH);

	PXCImage::ImageData depthData;
	PXCImage::ImageInfo depthInfo;
	PXCImage::ImageData RGBData;
	PXCImage::ImageInfo RGBInfo;


	//color_image->QueryInfo(&RGBInfo);
	//if(color_image->AcquireAccess(PXCImage::ACCESS_READ, &RGBData)>=PXC_STATUS_NO_ERROR){
	//cv::Mat RGBResult(RGBInfo.height, RGBInfo.width, CV_8UC3, RGBData.planes[0]);*/
	//bcg.findBackground(RGBResult);
	////	//FIXME: ci vorrà un filtraggio?? forse no, forse è dannoso

	//cout<<frameIstance<<endl;
	//if(frameIstance==firstFrame_){
	//rs.setMaskFromMouse(RGBResult);
	//rs.setMaskFromFile(); //per evitare di risettarli ad ogni run
	//}
	//	subtract(RGBResult,RGBResult,RGBResult,rs.getMask());

	//	if(frameIstance==firstFrame_){
	//		RGBbggmm=new BackgroundGMM(RGBResult);
	//	}
	//	if(checkFrameRange()){
	//		RGBbggmm->Processing(RGBResult);
	//		RGBbggmm->StoreImg(frameIstance,"rgb");
	//	}

	//RGBResult.release();
	//}

	depth_image->QueryInfo(&depthInfo);

	if(depth_image->AcquireAccess(PXCImage::ACCESS_READ, &depthData)>=PXC_STATUS_NO_ERROR){
		pxcBYTE* temp = computeDepthImage(depthData,depthInfo);
		cv::Mat depthResult(480, 640, CV_8UC3, temp);
		//	////	//FIXME: ci vorrà un filtraggio?? forse no, forse è dannoso
		//		subtract(depthResult,depthResult,depthResult,rs.getDepthMask());
		bcg.findBackground(depthResult);


		//	//	if(frameIstance==firstFrame_){
		//	//		depthbggmm=new BackgroundGMM(depthResult);
		//	//	}
		//	//	if(checkFrameRange()){
		//	//		depthbggmm->Processing(depthResult);
		//	//		depthbggmm->StoreImg(frameIstance,"depth");
		//	//	}
		depthResult.release();
		delete temp;
	}
	//	//color_image->ReleaseAccess(&RGBData);
	depth_image->ReleaseAccess(&depthData);




	//TODO: da completare
	//if(checkFrameRange()){
	//combinedSpaceAnalysis(RGBbggmm->getForeground(),naiveConvertDepthToGray(depthbggmm->getForeground()));
	//}

	return true;
}

void AnalyzePipeline::analyze() {
	//Size RGBSize = RGBFrame.getSize();
	//Size depthSize = depthFrame.getSize();
	//EnableImage(RGBFrame.getImageType());
	//EnableImage(depthFrame.getImageType());
	//this->LoopFrames();
	int frameNumber = 1;
	for(;;) {
		Mat frame;
		if(!player.read(frame)){
			break;
		}

		cout << "frame: " << frameNumber << endl;
		frameNumber++;
		bcg.findBackground(frame);
		waitKey(30);

	}


}


void AnalyzePipeline::combinedSpaceAnalysis(Mat rgb,Mat depth){

	cv::imshow("rgb",rgb);
	cv::waitKey(30);
	cv::moveWindow("rgb",0,0);

	cv::imshow("depth",depth);
	cv::waitKey(30);
	cv::moveWindow("depth",650,0);
	getchar();
	//TODO:anche qui non ci starebbe male un controllo di congruenza
	Mat result=Mat::zeros(Size(rgb.cols,rgb.rows),CV_8U);
	for(int i=0;i<rgb.rows;i++){
		for(int j=0;j<rgb.cols;j++){
			if( (rgb.at<uchar>(i,j)!=0)&&(depth.at<uchar>(i,j)!=0) )
				result.at<uchar>(i,j)=255;
		}
	}
	//cv::imshow("Spazio Combinato",result);
	//cv::waitKey(30);
	//cv::moveWindow("Spazio Combinato",0,0);
}

int AnalyzePipeline::getIstance(){
	return frameIstance;
}

//FIXME:Funzione di conversione consigliata dagli esperti, ma non completa al momento
Mat completeConvertDepthToRGB(Mat depthImage, PXCImage::ImageData pxcDepthImageData){

	PXCSession::ImplDesc impl;
	//FIXME:qui non so se sono corretti i 2 zeri
	Session::getSession()->QueryImpl(0,0,&impl);
	pxcUID uid=impl.iuid;
	PXCSmartPtr<PXCProjection> pj;
	Session::getSession()->DynamicCast<PXCMetadata>()->CreateSerializable<PXCProjection>(uid,&pj);

	int npoints = depthImage.rows * depthImage.cols; 

	PXCPoint3DF32* pos2d = new PXCPoint3DF32[npoints];

	PXCPointF32* posc = new PXCPointF32[npoints];
	for (int y = 0, k = 0; (pxcU32)y < depthImage.rows; y++)
	{
		for (int x = 0; (pxcU32)x < depthImage.cols; x++, k++)
		{
			// prepopulate the x and y values of the the depth data
			pos2d[k].x = (pxcF32)x;
			pos2d[k].y = (pxcF32)y;
			pos2d[k].z = ((short*)pxcDepthImageData.planes[0])[y * (pxcDepthImageData.pitches[0] / sizeof(pxcU16)) + x];
		}
	}
	pj->MapDepthToColorCoordinates(depthImage.rows * depthImage.cols, pos2d, posc);

	//TODO: riportare posc ad un Mat

	return depthImage;//Chiaramente errato
}

pxcBYTE* AnalyzePipeline::computeDepthImage(	PXCImage::ImageData depthData,PXCImage::ImageInfo depthInfo) {
	unsigned __int16* src = (unsigned __int16*)depthData.planes[1];
	pxcBYTE * frame = (pxcBYTE*) malloc (3*640*480*sizeof(unsigned __int8));
	//
	//float DEFAULT_SCALE = 30.0f;
	//float MAX_Z = 0.5f/13.0f;
	//float max_distance = MAX_Z;
	//float m_scale = 0.09f*320;
	//float range_min = .0f;
	//float range_max = max_distance * m_scale / DEFAULT_SCALE;
	//

	for(int j=0; j < 640*480; j++) {
		frame[3*j] = 0;
		frame[(3*j)+1] = 0;
		frame[(3*j)+2] = 0;
	}


	for(int j=0; j < 320*240; j++) {
		float val = (float)src[j] / 65535;
		//	val = 1.f - ((val-range_min)/(range_max-range_min));
		val = 1.f - (float)( ((val)/(0.015)));
		val = max(val, 0.f);
		val = min(val, 1.f);



		float *uvmap=(float*)depthData.planes[2];

		int x = j%320;
		int y = floor(j/320);
		int index=((int)y)*320+x;
		//cout << x << " " << y << endl;
		if(uvmap[index*2] > 0 && uvmap[index*2+1] > 0) {
			float newX = uvmap[(index*2)]*640;
			float newY = uvmap[(index*2)+1]*480;

			//cout << newX << " " << newY << endl;

			//unsigned __int8* rgb = (unsigned __int8*) (&dst[3*j]);


			int index = (int)( (( (int)newY*640) + ((int)newX) ));

			//cout << index << endl;

			frame[(3*index)] = (unsigned __int8)(255*val);
			frame[(3*index)+1] = (unsigned __int8)(255*val);
			frame[(3*index)+2] = (unsigned __int8)(255*val);

		}



	}

	for(int j=0; j < 640*480; j++) {

		//	//FIXME: se per caso devo fare la media pesata allora devo fare un vero buffer, e non un semplice array di array

		buffer[j][frameIstance%3] = frame[j];
		buffer[j+1][frameIstance%3] = frame[j+1];
		buffer[j+2][frameIstance%3] = frame[j+2];
	}

	for(int j=0; j < 640*480; j++) {

		if(frameIstance > 1){
			//	//FIXME: se per caso devo fare la media pesata allora devo fare un vero buffer, e non un semplice array di array

			frame[j] = (int) (((float)buffer[j][0] + buffer[j][1] + buffer[j][2]) / 3);

			//cout << endl << endl << endl << (float)buffer[j][0] << " " << (float)buffer[j][1] << " " << (float)buffer[j][2] << endl;
			//cout << (int)(((float)buffer[j][0] + buffer[j][1] + buffer[j][2]) / 3);

			frame[j+1] = (int) (((float)buffer[j+1][0] + buffer[j+1][1] + buffer[j+1][2]) / 3);

			//cout << endl << endl << endl << (float)buffer[j+1][0] << " " << (float)buffer[j+1][1] << " " << (float)buffer[j+1][2] << endl;
			//cout << (int)(((float)buffer[j+1][0] + buffer[j+1][1] + buffer[j+1][2]) / 3);

			frame[j+2] = (int) (((float)buffer[j+2][0] + buffer[j+2][1] + buffer[j+2][2]) / 3);

			//cout << endl << endl << endl << (float)buffer[j+2][0] << " " << (float)buffer[j+2][1] << " " << (float)buffer[j+2][2] << endl;
			//cout << (int)(((float)buffer[j+2][0] + buffer[j+2][1] + buffer[j+2][2]) / 3);
			//cout << "test " << (int)frame[j+1] << endl;
			//getchar();
		} 
	}

	frameIstance++;
	//cout << "finito" << endl;


	return frame;


}