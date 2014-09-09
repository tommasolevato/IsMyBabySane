#include "MatDeleter.h"

void MatDeleter::deleteMat(Mat toDelete) {
	delete toDelete.data;
}