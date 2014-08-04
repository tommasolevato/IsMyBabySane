#include "CommandLineArgumentParser.h"
#include <algorithm>

using namespace std;

string CommandLineArgumentParser::getCmdOption(const std::string & option) {

	char ** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
	{
		return *itr;
	}
	return 0;

}


bool CommandLineArgumentParser::cmdOptionExists(const std::string& option) {

	return std::find(begin, end, option) != end;

}