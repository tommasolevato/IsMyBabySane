#include "Converter.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Usage: isMyBabySane FILENAMETOCONVERT" << endl;
		exit(0);
	}
	Converter c(argv[1]);
	//Converter c(L"E:/Acquisizioni Meyer/Registrazione1_incubatrice");
	c.convert();
}


