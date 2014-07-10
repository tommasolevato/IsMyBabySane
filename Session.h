#ifndef SESSION_H
#define SESSION_H


#include <pxcsession.h>

class Session {
public:
	static PXCSession* getSession();

private:
	static PXCSession* session;
};

#endif