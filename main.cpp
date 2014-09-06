#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
#include "RGBPlayer.h"
#include "DepthPlayer.h"
#include "CommandLineArgumentParser.h"
#include "ElaboratedDepthPlayer.h"
#include "MatEncoder.h"

using namespace std;

int main(int argc, char* argv[]) {

	//VideoCapture player("E:/Acquisizioni Meyer/Registrazione3_incubatrice_Depth.avi");
	//Mat frame(480, 640, CV_8UC3);
	//player.read(frame);
	//MatEncoder encoder;
	////frame = encoder.threeChannels8bitsTo1Channel16Bits(frame);

	//VideoWriter writer;
	//writer.open("C:/Users/Tommaso/Desktop/pippo.avi", CV_FOURCC('X', 'V', 'I', 'D'), 30, Size(640, 480), true);

	//for(int i=0; i<500; i++) {
	//	writer.write(frame);
	//	imshow("Converting", frame);
	//	waitKey(30);
	//}

	//writer.release();

	//TODO: rimuovere
	/*list<int> lista;
	
	for(int i = 0; i < 10; i++) {
		lista.push_back(i);
	}

	for(list<int>::iterator it = lista.begin(); it!= lista.end(); it++) {
		cout << *it << endl;
	}

	cout << endl;

	for(list<int>::reverse_iterator it = lista.rbegin(); it!= lista.rend(); it++) {
		cout << *it << endl;
	}*/

	//exit(0);

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