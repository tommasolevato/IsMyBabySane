#include "Converter.h"
#include "AnalyzePipeline.h"
#include <iostream>
#include <string>
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
		//Converter c("C:/Users/Tommaso/Desktop/testCreative");
		//c.convert();

		//Questo costruttore prende inizio e fine frame per analizzare uno spezzone di video
		//AnalyzePipeline c(L"C:/Users/Tommaso/Desktop/testCreative_RGB.avi");
		//AnalyzePipeline c(L"E:/Acquisizioni Meyer/Registrazione3_incubatrice_RGB.avi");
		AnalyzePipeline c(L"C:/Users/Tommaso/Desktop/Filmato.mp4");
		c.analyze();

		//getchar();
	}
	catch( std::exception& e ){
		string err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
		getchar();
	}
}


