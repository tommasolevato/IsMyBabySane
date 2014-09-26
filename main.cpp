#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
#include "RGBPlayer.h"
#include "CommandLineArgumentParser.h"
#include "ElaboratedDepthPlayer.h"
#include "MatEncoder.h"

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

			if(parser.cmdOptionExists("-ns")) {
				analyzer.setNumberOfFramesForSmoothing(stoi(parser.getCmdOption("-ns")));
			}

			if(parser.cmdOptionExists("-nbe")) {
				analyzer.setNumberOfFramesForFalseBlackElimination(stoi(parser.getCmdOption("-nbe")));
			}

			analyzer.analyze();
			exit(0);
		}

		if(parser.cmdOptionExists("-pd")) {
			string depthFile   = parser.getCmdOption("-pd");
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