#pragma once
#include "DBJobQueue.h"
#include "MYSQLHelper.h"
#include "RedisManager.h"
class LoginDBJobQueue : public DBJobQueue
{
public:
	MYSQLHelper _accountDB;
	RedisManager _loginTokenRedis;
	void ProcReqLogin(class LoginServer* loginServer, SessionInfo sessionInfo, INT64 accountNo, Array<char, 64> sessionKey);
	LoginDBJobQueue();
};