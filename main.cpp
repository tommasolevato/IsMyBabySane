#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
#include "VideoPlayer.h"


using namespace std;

int main(int argc, char* argv[]) {
	//if(argc < 2) {
	//	cout << "Usage: isMyBabySane FILENAMETOCONVERT" << endl;
	//	exit(0);
	//}
	////Converter c(argv[1]);
	//Converter c("C:/Users/Tommaso/Desktop/testCreative");

	try{
		//Converter c("E:/Acquisizioni Meyer/Registrazione3_incubatrice");
		//Converter c("C:/Users/Tommaso/Desktop/AIV/testCreative");
		//c.convert();



		//unsigned int test = 511;

		//int test2 = (unsigned char) test;
		//cout << (int)test2;
		//getchar();
		//Questo costruttore prende inizio e fine frame per analizzare uno spezzone di video
		//AnalyzePipeline c(L"C:/Users/Tommaso/Desktop/AIV/testCreative_RGB.avi");
		
		AnalyzePipeline c(L"E:/Acquisizioni Meyer/Registrazione3_incubatrice_RGB.avi");
		//AnalyzePipeline c(L"C:/Users/Tommaso/Desktop/Filmato.mp4");
		c.analyze();

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


