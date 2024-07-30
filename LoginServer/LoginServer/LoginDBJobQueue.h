#pragma once
#include "MYSQLHelper.h"
#include "RedisHelper.h"
#include "JobQueue.h"
class LoginDBJobQueue : public JobQueue
{
public:
	MYSQLHelper _accountDB;
	RedisHelper _loginTokenRedis;
	void ProcReqLogin(class LoginServer* loginServer, SessionInfo sessionInfo, INT64 accountNo, Array<char, 64> sessionKey);
	LoginDBJobQueue(HANDLE hCompletionPort);
};