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
		//Converter c("F:/Leonardo/LeoWindows/Registrazioni Meyer/Registrazione3_incubatrice");
		//c.convert();

		//Questo costruttore prende inizio e fine frame per analizzare uno spezzone di video
		AnalyzePipeline c(L"F:/Leonardo/LeoWindows/Registrazioni Meyer/Registrazione3_incubatrice");
		c.analyze();
	}
	catch( cv::Exception& e ){
		const char* err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
		getchar();
	}
}


