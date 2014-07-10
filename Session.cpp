#include "Session.h"


PXCSession* Session::session;

PXCSession* Session::getSession() {
	if(session == NULL)
		PXCSession_Create(&session);
	return session;
}