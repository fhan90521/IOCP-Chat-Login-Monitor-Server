#include "LoginDBJobQueue.h"
#include "LoginServer.h"
#include "CommonProtocol.h"
void LoginDBJobQueue::ProcReqLogin(LoginServer* loginServer ,SessionInfo sessionInfo, INT64 accountNo, Array<char, 64> sessionKey)
{
	MYSQL* DBconnection = _accountDB.GetConnection();
	char getAccountInfoQuery[512];
	MYSQLHelper::MakeQuery(getAccountInfoQuery, 512, "SELECT* FROM accountdb.account where accountno = %d", accountNo);
	int queryStat = mysql_query(DBconnection, getAccountInfoQuery);
	if (queryStat != 0)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "Mysql query error : %s\n", mysql_error(DBconnection));
		_accountDB.CloseConnection();
		for (int i = 0; i < 1; i++)
		{
			if (_accountDB.Connect() == true && mysql_query(DBconnection = _accountDB.GetConnection(), getAccountInfoQuery) == 0)
			{
				break;
			}
			_accountDB.CloseConnection();
		}
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
	_loginTokenRedis.GetRedisConnection()->setex(std::to_string(accountNo), 30, sessionKey.data(), [loginServer, sessionInfo,accountNo ,userId, userNick](cpp_redis::reply& reply) mutable
		{
			if (reply.is_simple_string() == true)
			{
				loginServer->ResLogin(sessionInfo, accountNo, dfLOGIN_STATUS_OK, userId, userNick, loginServer->_gameServerIpArr, loginServer->_gameServerPort, loginServer->_chatServerIpArr, loginServer->_chatServerPort, true);
				InterlockedIncrement(&loginServer->_procLoginReqCnt);
			}
			else
			{
				Log::LogOnFile(Log::SYSTEM_LEVEL, "redis set fail\n");
			}
		}
	);
	_loginTokenRedis.GetRedisConnection()->sync_commit();
}

LoginDBJobQueue::LoginDBJobQueue(HANDLE hCompletionPort): JobQueue(hCompletionPort) , _accountDB("LoginServerSetting.json"), _loginTokenRedis("LoginServerSetting.json")
{
}
