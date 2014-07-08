#include <pxcsession.h>
#include <pxcmetadata.h>
#include <pxcsmartptr.h>
#include <util_pipeline.h>
#include <pxcimage.h>
#include "RGBPipeline.h"

#include <iostream>

using namespace std;

int main() {
	PXCSession* session;
	PXCSession_Create(&session);

	PXCMetadata *mdata = session->DynamicCast<PXCMetadata>();

	RGBPipeline pp(session, L"testCreative", false);
	
	//MyPipeline pp(session, L"testCreative", false);

	pp.EnableImage(PXCImage::COLOR_FORMAT_DEPTH);
	pp.LoopFrames();

	pp.finalize();
}