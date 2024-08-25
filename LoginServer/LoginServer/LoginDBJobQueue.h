#pragma once
#include "JobQueue.h"
#include "Session.h"
class LoginDBJobQueue : public JobQueue
{
public:
	class LoginServer* _loginServer=nullptr;
	class MYSQLHelper& _accountDB;
	class RedisHelper& _loginTokenRedis;
	void ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey);
	LoginDBJobQueue(class LoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB, RedisHelper& loginTokenRedis);
};