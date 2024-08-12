#pragma once
#include "MYSQLHelper.h"
#include "RedisHelper.h"
#include "JobQueue.h"
class LoginDBJobQueue : public JobQueue
{
public:
	class LoginServer* _loginServer=nullptr;
	MYSQLHelper _accountDB;
	RedisHelper _loginTokenRedis;
	void ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey);
	LoginDBJobQueue(class LoginServer* loginServer, HANDLE hCompletionPort);
};