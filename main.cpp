#include "Converter.h"
#include <iostream>
#include <string>
using namespace std;

<<<<<<< HEAD
int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Usage: isMyBabySane FILENAMETOCONVERT" << endl;
		exit(0);
	}
	Converter c(argv[1]);
	//Converter c(L"E:/Acquisizioni Meyer/Registrazione1_incubatrice");
=======
int main() {
	Converter c(L"C:/Users/Tommaso/Desktop/testCreative");
>>>>>>> parent of 3a91e7f... Fix: Memory Leak
	c.convert();

	cout << "Ho finito!" << endl;
	getchar();

	//InfoPipeline info(L"C:/Users/Tommaso/Desktop/testCreative");
	//cout << info.getTotalNumberOfFrames() << endl;
	//cout << info.getTotalNumberOfFrames() << endl;
	//cout << info.getTotalNumberOfFrames() << endl;
	//getchar();
}


