#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
#include "RGBPlayer.h"
#include "DepthPlayer.h"
#include "CommandLineArgumentParser.h"
#include "ElaboratedDepthPlayer.h"

using namespace std;

int main(int argc, char* argv[]) {

	CommandLineArgumentParser parser(argv, argc);

	try{
		if(parser.cmdOptionExists("-c")) {
			string intelFile = parser.getCmdOption("-c");
			Converter converter(intelFile.c_str());
			converter.convert();
			exit(0);
		}

		if(parser.cmdOptionExists("-rgb") && parser.cmdOptionExists("-d")) {
			string rgbFile   = parser.getCmdOption("-rgb");
			string depthFile = parser.getCmdOption("-d");

			AnalyzePipeline analyzer(rgbFile, depthFile);
			analyzer.analyze();
			exit(0);
		}

		if(parser.cmdOptionExists("-p")) {
			string rgbFile   = parser.getCmdOption("-p");
			RGBPlayer p(rgbFile);
			p.playAndSaveFrames();
			exit(0);
		}

		if(parser.cmdOptionExists("-pd")) {
			string depthFile   = parser.getCmdOption("-pd");
			//TODO: cambiare (forse)
			ElaboratedDepthPlayer p(depthFile);
			p.play();
			exit(0);
		}
		
	}
	catch( std::exception& e ){
		string err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
		getchar();
	}
}


// -c C:/Users/Tommaso/Desktop/AIV/testCreative      -rgb C:/Users/Tommaso/Desktop/AIV/testCreative_RGB.avi      -d C:/Users/Tommaso/Desktop/AIV/testCreative_Depth.avi
// -c "E:/Acquisizioni Meyer/Registrazione3_incubatrice"      -rgb "E:/Acquisizioni Meyer/Registrazione3_incubatrice_RGB.avi"      -d "E:/Acquisizioni Meyer/Registrazione3_incubatrice_Depth_lags.avi"
// -pd "E:/Acquisizioni Meyer/Registrazione3_incubatrice_Depth_lags.avi"
// -pd "E:/Acquisizioni Meyer/Registrazione3_incubatrice_Depth.avi"