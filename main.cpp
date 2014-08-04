#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
#include "VideoPlayer.h"
#include "CommandLineArgumentParser.h"

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

		//VideoPlayer p("C:/Users/Tommaso/Desktop/AIV/testCreative_Depth.avi");
		//p.playAndSaveFrames();
		
		//p.play("C:/Users/Tommaso/Desktop/AIV/testCreative_RGB.avi");
	}
	catch( std::exception& e ){
		string err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
		getchar();
	}
}


// -c C:/Users/Tommaso/Desktop/AIV/testCreative      -rgb C:/Users/Tommaso/Desktop/AIV/testCreative_RGB.avi      -d C:/Users/Tommaso/Desktop/AIV/testCreative_Depth.avi
// -c E:/Acquisizioni Meyer/Registrazione3_incubatrice      -rgb E:/Acquisizioni Meyer/Registrazione3_incubatrice_RGB.avi      -d E:/Acquisizioni Meyer/Registrazione3_incubatrice_Depth.avi