#pragma once


#include <locale>
#include <sstream>
#include <string>

using namespace std;

class Util {
public:
	//TODO: cambiare nome
	static std::string WChartToStdString(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale());
};