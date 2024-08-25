#include "LoginDBJobQueue.h"
#include "LoginServer.h"
#include "CommonProtocol.h"
void LoginDBJobQueue::ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey)
{
	MYSQL* DBconnection = _accountDB.GetConnection();
	MYSQL_BIND binds[1];
	bool isNulls[1] = { false };
	MYSQLHelper::InitBind(binds, isNulls,accountNo);
	bool retSendQuery=_accountDB.SendQuery( "SELECT* FROM accountdb.account where accountno = ?", binds);
	if (retSendQuery == false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "SendQuery Error\n");
		_accountDB.CloseConnection();
		return;
	}
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	Array<WCHAR, 20> userId;
	Array<WCHAR, 20> userNick;
	sql_result = mysql_store_result(DBconnection);
	if (sql_result)
	{
		sql_row = mysql_fetch_row(sql_result);
		MultiByteToWideChar(CP_ACP, 0, sql_row[1], strlen(sql_row[1]) + 1, userId.data(), 20);
		MultiByteToWideChar(CP_ACP, 0, sql_row[3], strlen(sql_row[3]) + 1, userNick.data(), 20);
		mysql_free_result(sql_result);
	}
	_loginTokenRedis.GetRedisConnection()->setex(std::to_string(accountNo), 30, sessionKey.data(), [this, sessionInfo,accountNo ,userId, userNick](cpp_redis::reply& reply) mutable
		{
			if (reply.is_simple_string() == true)
			{
				_loginServer->ResLogin(sessionInfo, accountNo, dfLOGIN_STATUS_OK, userId, userNick, _loginServer->GetGameServerIp(), _loginServer->GetGameServerPort(), _loginServer->GetChatServerIp(), _loginServer->GetChatServerPort(), true);
				_loginServer->IncrementLoginReqCnt();
			}
			else
			{
				Log::LogOnFile(Log::SYSTEM_LEVEL, "redis set fail\n");
			}
		}
	);
	_loginTokenRedis.GetRedisConnection()->commit();
}

LoginDBJobQueue::LoginDBJobQueue(class LoginServer* loginServer, HANDLE hCompletionPort):
	_loginServer(loginServer),
	JobQueue(hCompletionPort) ,
	_accountDB("LoginServerSetting.json"),
	_loginTokenRedis("LoginServerSetting.json")
{

}
