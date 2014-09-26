#pragma once


#include <locale>
#include <sstream>
#include <string>

using namespace std;

class Util {
public:
	static std::string WChartToStdString(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale());
};