#include "LoginServer.h"
#include "MyNew.h"
#include "CommonProtocol.h"
#include <format>
#include "MonitorProtocol.h"
#include "ParseJson.h"
#include "Log.h"
bool LoginServer::OnAcceptRequest(const char* ip, USHORT port)
{
	return true;
}

void LoginServer::OnAccept(SessionInfo sessionInfo)
{
	InterlockedIncrement64(&_onConnectCnt);
	return;
}

void LoginServer::OnDisconnect(SessionInfo sessionInfo)
{
	return;
}

void LoginServer::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	if (PacketProc(sessionInfo, buf) == false)
	{
		Disconnect(sessionInfo);
	}
}

void LoginServer::Run()
{
	IOCPRun();
}

void LoginServer::ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey)
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
			if (_accountDB.Connect() == true&& mysql_query(DBconnection= _accountDB.GetConnection(), getAccountInfoQuery)==0)
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
	std::future<cpp_redis::reply> futureReply= _loginTokenRedis.GetRedisConnection()->setex(std::to_string(accountNo),30,sessionKey.data());
	_loginTokenRedis.GetRedisConnection()->sync_commit();
	cpp_redis::reply reply= futureReply.get();
	if (reply.is_simple_string()==false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "redis set fail\n");
	}
	String ip;
	GetClientIp(sessionInfo, ip);
	ResLogin(sessionInfo, accountNo, dfLOGIN_STATUS_OK, userId, userNick, _gameServerIpArr, _gameServerPort, _chatServerIpArr, _chatServerPort, true);
	InterlockedIncrement(&_procLoginReqCnt);
}

void LoginServer::Monitor()
{
	int bufAllocCnt = CSendBuffer::GetAllocCnt();
	_monitor.UpdateMonitorData();
	std::cout << std::format(R"(
-------------------------------------
SessionNum: {}
 
Accept Total: {}                                   
Accept Tps: {}
RecvMessageTps: {}
SendMessageTps: {}
_reservQ size: {}
_reservList size : {}
)", GetConnectingSessionCnt(), _onConnectCnt, GetAcceptCnt(), GetRecvCnt(), GetSendCnt(),_reserveDisconnectQ.Size(),_reserveDisconnectList.size());
	time_t currentTime;
	time(&currentTime);
	if (_monitorClient._bLoginSuccess)
	{
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_SERVER_RUN, true, currentTime);
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_SERVER_CPU, _monitor.GetProcessCpuTotal(), currentTime);
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_SERVER_MEM, _monitor.GetProcessUserMemoryByMB(), currentTime);
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_SESSION, GetConnectingSessionCnt(), currentTime);
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_AUTH_TPS, GetProcLoginReqCnt(), currentTime);
		_monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_LOGIN_PACKET_POOL, bufAllocCnt, currentTime);
	}
}

LoginServer::~LoginServer()
{
	CloseServer();
}

LoginServer::LoginServer() : LoginServerProxy(this), IOCPServer("LoginServerSetting.json"), _accountDB("LoginServerSetting.json"), _loginTokenRedis("LoginServerSetting.json")
{
	Document serverSetValues = ParseJson("LoginServerSetting.json");
	std::string chatServerIp = serverSetValues["ChatServerIp"].GetString();
	std::wstring wChatServerIp;
	wChatServerIp.assign(chatServerIp.begin(), chatServerIp.end());
	std::copy(wChatServerIp.begin(), wChatServerIp.end(), _chatServerIpArr.begin());

	std::string gameServerIp = serverSetValues["GameServerIp"].GetString();
	std::wstring wGameServerIp;
	wGameServerIp.assign(gameServerIp.begin(), gameServerIp.end());
	std::copy(wGameServerIp.begin(), wGameServerIp.end(), _gameServerIpArr.begin());

	_chatServerPort = serverSetValues["ChatServerPort"].GetInt();
	_gameServerPort = serverSetValues["GameServerPort"].GetInt();
	_monitorClient.Run();
}