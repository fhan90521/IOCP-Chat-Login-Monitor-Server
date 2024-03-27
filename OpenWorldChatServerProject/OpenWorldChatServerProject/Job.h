#pragma once
#include "MyWindow.h"
#include "Session.h"
struct Job
{
	SessionInfo _sessionInfo;
	class ChatServer* _pServer;
	virtual void ProcessJob() = 0;
public:
	virtual ~Job() {};
};