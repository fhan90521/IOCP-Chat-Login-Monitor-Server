#pragma once
#include "DBJobQueue.h"
#include "MYSQLHelper.h"
#include "RedisHelper.h"
class LoginDBJobQueue : public DBJobQueue
{
public:
	MYSQLHelper _accountDB;
	RedisHelper _loginTokenRedis;
	void ProcReqLogin(class LoginServer* loginServer, SessionInfo sessionInfo, INT64 accountNo, Array<char, 64> sessionKey);
	LoginDBJobQueue();
};