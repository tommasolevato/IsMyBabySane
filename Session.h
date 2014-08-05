#pragma once


#include <pxcsession.h>

class Session {
public:
	static PXCSession* getSession();



private:
	static PXCSession* session;
};