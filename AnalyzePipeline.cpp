#include "AnalyzePipeline.h"
#include "AnalysisLib.h"
#include <pxcprojection.h>
#include <pxcmetadata.h>

using namespace std;
using namespace cv;

Mat completeConvertDepthToRGB(Mat depthImage, PXCImage::ImageData pxcDepthImageData);
Mat naiveConvertDepthToGray(Mat depthImage);
pxcBYTE* computeDepthImage(	PXCImage::ImageData depthData,PXCImage::ImageInfo depthInfo);


bool AnalyzePipeline::checkFrameRange(){
	return (frameIstance>firstFrame_&&frameIstance<lastFrame_);
}


bool AnalyzePipeline::OnNewFrame() {
	frameIstance++;
	cout<<"\r"<<"               \r"<<frameIstance<<"    ";

	PXCImage *color_image=QueryImage(PXCImage::IMAGE_TYPE_COLOR);
	PXCImage *depth_image=QueryImage(PXCImage::IMAGE_TYPE_DEPTH);

	PXCImage::ImageData depthData;
	PXCImage::ImageInfo depthInfo;
	PXCImage::ImageData RGBData;
	PXCImage::ImageInfo RGBInfo;

	color_image->QueryInfo(&RGBInfo);
	if(color_image->AcquireAccess(PXCImage::ACCESS_READ, &RGBData)>=PXC_STATUS_NO_ERROR){
		cv::Mat RGBResult(RGBInfo.height, RGBInfo.width, CV_8UC3, RGBData.planes[0]);
		//FIXME: ci vorrà un filtraggio?? forse no, forse è dannoso

		cout<<frameIstance<<endl;
		if(frameIstance==firstFrame_){
			rs.setMaskFromMouse(RGBResult);
			//rs.setMaskFromFile(); //per evitare di risettarli ad ogni run
		}
		subtract(RGBResult,RGBResult,RGBResult,rs.getMask());

		if(frameIstance==firstFrame_){
			RGBbggmm=new BackgroundGMM(RGBResult);
		}
		if(checkFrameRange()){
			RGBbggmm->Processing(RGBResult);
			RGBbggmm->StoreImg(frameIstance,"rgb");
		}

		RGBResult.release();
	}

	depth_image->QueryInfo(&depthInfo);
	if(depth_image->AcquireAccess(PXCImage::ACCESS_READ, &depthData)>=PXC_STATUS_NO_ERROR){	
		cv::Mat depthResult(depthInfo.height, depthInfo.width, CV_16U, computeDepthImage(depthData,depthInfo));
		//FIXME: ci vorrà un filtraggio?? forse no, forse è dannoso

		subtract(depthResult,depthResult,depthResult,rs.getDepthMask());

		if(frameIstance==firstFrame_){
			depthbggmm=new BackgroundGMM(depthResult);
		}
		if(checkFrameRange()){
			depthbggmm->Processing(depthResult);
			depthbggmm->StoreImg(frameIstance,"depth");
		}
		depthResult.release();
	}
	color_image->Release();
	depth_image->Release();

	//TODO: da completare
	//if(checkFrameRange()){
	//	combinedSpaceAnalysis(RGBbggmm->getForeground(),naiveConvertDepthToGray(depthbggmm->getForeground()));
	//}

	return true;
}

void AnalyzePipeline::analyze() {
	Size RGBSize = RGBFrame.getSize();
	Size depthSize = depthFrame.getSize();
	EnableImage(RGBFrame.getImageType());
	EnableImage(depthFrame.getImageType());
	this->LoopFrames();
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

Mat naiveConvertDepthToGray(Mat depthImage){

	Mat convertedDepth=Mat::zeros(Size(640,480),CV_8U);
	for(int i=0;i<depthImage.rows;i++){
		for(int j=0;j<depthImage.cols;j++){
			convertedDepth.at<uchar>(2*i,2*j)=depthImage.at<uchar>(i,j);
			convertedDepth.at<uchar>(2*i+1,2*j)=depthImage.at<uchar>(i,j);
			convertedDepth.at<uchar>(2*i,2*j+1)=depthImage.at<uchar>(i,j);
			convertedDepth.at<uchar>(2*i+1,2*j+1)=depthImage.at<uchar>(i,j);
		}
	}
	return convertedDepth;
}

pxcBYTE* computeDepthImage(	PXCImage::ImageData depthData,PXCImage::ImageInfo depthInfo) {
	unsigned __int16* src = (unsigned __int16*)depthData.planes[0];
	pxcBYTE* result = (pxcBYTE*) malloc (3*depthInfo.width*depthInfo.height*sizeof(pxcBYTE));
	
	float DEFAULT_SCALE = 30.0f;
	float MAX_Z = 0.5f/13.0f;
	float max_distance = MAX_Z;
	float m_scale = 0.09f*320;
	float range_min = .0f;
	float range_max = max_distance * m_scale / DEFAULT_SCALE;
	
	for(int j=0; j < depthInfo.width*depthInfo.height; j++) {
		float val = (float)src[j] / 65535;
		val = 1.f - ((val-range_min)/(range_max-range_min));
		val = max(val, 0.f);
		val = min(val, 1.f);
		//unsigned __int8* rgb = (unsigned __int8*) (&dst[3*j]);

		result[3*j] = (unsigned __int8)(255*val);
		result[(3*j)+1] = (unsigned __int8)(255*val);
		result[(3*j)+2] = (unsigned __int8)(255*val);
	}
	return result;
}