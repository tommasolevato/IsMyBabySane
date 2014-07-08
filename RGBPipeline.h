#include <util_pipeline.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class RGBPipeline : public UtilPipeline {

private:
	VideoWriter writer;

public: 
	RGBPipeline(PXCSession *session, const pxcCHAR *file, bool recording) : UtilPipeline(session, file, recording) {
		Size s(640, 480);
		writer.open("C:/Users/Tommaso/Desktop/1.avi", CV_FOURCC('X','V','I', 'D'), 30, s, true);
	}
	void OnImage(PXCImage *image);

	void finalize();
};