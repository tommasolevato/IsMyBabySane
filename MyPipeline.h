#include <util_pipeline.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class MyPipeline : public UtilPipeline {

private:
	VideoWriter writer;

public: 
	MyPipeline(PXCSession *session, const pxcCHAR *file, bool recording) : UtilPipeline(session, file, recording) {
		Size s(320, 240);
		writer.open("C:/Users/Tommaso/Desktop/pippo.mpeg", CV_FOURCC('D','I','B', ' '), 30, s, false);
	}
	void OnImage(PXCImage *image);

	void finalize();
};