#include <pxcsession.h>
#include <pxcmetadata.h>
#include <pxcsmartptr.h>
#include <util_pipeline.h>
#include <pxcimage.h>
#include "ConvertPipeline.h"
#include "InfoPipeline.h"

#include <iostream>

using namespace std;

int main() {
	/*ConvertPipeline converter(L"C:/Users/Tommaso/Desktop/testCreative");
	converter.convert();*/

	InfoPipeline info(L"C:/Users/Tommaso/Desktop/testCreative");
	cout << info.getTotalNumberOfFrames() << endl;
	cout << info.getTotalNumberOfFrames() << endl;
	cout << info.getTotalNumberOfFrames() << endl;
	getchar();
}
