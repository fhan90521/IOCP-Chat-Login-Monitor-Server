#include "LoginServer.h"
#include "MyNew.h"
#include "CommonProtocol.h"
#include <format>
#include "MonitorProtocol.h"
#include "ParseJson.h"
#include "Log.h"
#include "LoginDBJobQueue.h"
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
	_loginDBJobQueue->PushDBJob(&LoginDBJobQueue::ProcReqLogin,this,sessionInfo,accountNo,sessionKey);
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

LoginServer::LoginServer() : LoginServerProxy(this), IOCPServer("LoginServerSetting.json")
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

	_loginDBJobQueue = new LoginDBJobQueue;

	_chatServerPort = serverSetValues["ChatServerPort"].GetInt();
	_gameServerPort = serverSetValues["GameServerPort"].GetInt();
	_monitorClient.Run();
}