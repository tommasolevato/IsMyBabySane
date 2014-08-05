#pragma once


#include <string>

using namespace std;

class CommandLineArgumentParser {
public:
	CommandLineArgumentParser(char** argv, int argc) {
		begin = argv;
		end = argv + argc;
	}

	string getCmdOption(const std::string & option);
	bool cmdOptionExists(const std::string& option);



private:
	char** begin;
	char** end;
};