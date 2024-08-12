#include "LoginServer.h"
#include "MyNew.h"
#include "CommonProtocol.h"
#include <format>
#include "MonitorProtocol.h"
#include "ParseJson.h"
#include "Log.h"
#include "LoginDBJobQueue.h"
#include "MakeShared.h"
const Array<WCHAR, 16>& LoginServer::GetChatServerIp()
{
	return _chatServerIp;
}
USHORT LoginServer::GetChatServerPort()
{
	return _chatServerPort;
}
const Array<WCHAR, 16>& LoginServer::GetGameServerIp()
{
	return _gameServerIp;
}
USHORT LoginServer::GetGameServerPort()
{
	return _gameServerPort;
}
void LoginServer::IncrementLoginReqCnt()
{
	InterlockedIncrement(&_procLoginReqCnt);
}
LONG LoginServer::GetProcLoginReqCnt()
{
	int ret = _procLoginReqCnt;
	InterlockedExchange(&_procLoginReqCnt, 0);
	return ret;	
}
void LoginServer::CheckLastRecvTime()
{
	while (1)
	{
		DWORD retWait = WaitForSingleObject(_hShutDownEvent, RECV_TIME_OUT);
		if (retWait == WAIT_OBJECT_0)
		{
			break;
		}
		{
			SHARED_LOCK;
			ULONG64 curTime = GetTickCount64();
			for (auto& pairTemp : _sessionMap)
			{
				LastRecvTime lastRecvTime = pairTemp.second;
				if (curTime - lastRecvTime > RECV_TIME_OUT)
				{
					Disconnect(pairTemp.first);
				}
			}
		}

	}
}
bool LoginServer::OnAcceptRequest(const char* ip, USHORT port)
{
	return true;
}

void LoginServer::OnAccept(SessionInfo sessionInfo)
{
	InterlockedIncrement64(&_onConnectCnt);
	EXCLUSIVE_LOCK;
	_sessionMap[sessionInfo.Id()] = GetTickCount64();
	return;
}

void LoginServer::OnDisconnect(SessionInfo sessionInfo)
{
	EXCLUSIVE_LOCK;
	_sessionMap.erase(sessionInfo.Id());
	return;
}

void LoginServer::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	if (PacketProc(sessionInfo, buf) == false)
	{
		Disconnect(sessionInfo);
	}
	else
	{
		//SESSION마다 RECV1회제한->_sessionMap에 특정 세션의 lastRecvTime을 고치고 있는 스레드는 하나일 수 밖에 없음->SHARED_LOCK만 걸고 쓰기해도 됨
		//OnDisconnect 이후로는 동일 sessionID로 OnRecv가 호출 안됨 굳이 find하지 않고 바로 대입가능
		SHARED_LOCK;
		_sessionMap[sessionInfo.Id()] = GetTickCount64();
	}
}

void LoginServer::Run()
{
	IOCPRun();
}

void LoginServer::ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey)
{
	int index = (_dbQueueIndex++) % _dbJobQueues.size();
	_dbJobQueues[index]->DoAsync(&LoginDBJobQueue::ProcReqLogin,sessionInfo, accountNo, sessionKey);
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
	SetEvent(_hShutDownEvent);
	_checkRecvTimeThread->join();
	delete _checkRecvTimeThread;
	CloseServer();
	delete _dbWorkThreadPool;
}

LoginServer::LoginServer() : LoginServerProxy(this), IOCPServer("LoginServerSetting.json")
{

	Document serverSetValues = ParseJson("LoginServerSetting.json");
	std::string chatServerIp = serverSetValues["ChatServerIp"].GetString();
	std::wstring wChatServerIp;
	wChatServerIp.assign(chatServerIp.begin(), chatServerIp.end());
	std::copy(wChatServerIp.begin(), wChatServerIp.end(), _chatServerIp.begin());

	std::string gameServerIp = serverSetValues["GameServerIp"].GetString();
	std::wstring wGameServerIp;
	wGameServerIp.assign(gameServerIp.begin(), gameServerIp.end());
	std::copy(wGameServerIp.begin(), wGameServerIp.end(), _gameServerIp.begin());

	_dbWorkThreadPool = new WorkThreadPool(_dbConcurrentWorkThreadCnt, _dbConcurrentWorkThreadCnt *2);
	for (int i = 0; i < _dbConcurrentWorkThreadCnt; i++)
	{
		_dbJobQueues.push_back(MakeShared<LoginDBJobQueue>(this,_dbWorkThreadPool->GetCompletionPortHandle()));
	}
	
	_chatServerPort = serverSetValues["ChatServerPort"].GetInt();
	_gameServerPort = serverSetValues["GameServerPort"].GetInt();
	_monitorClient.Run();

	_hShutDownEvent = CreateEvent(NULL, TRUE, false, NULL);
	_checkRecvTimeThread = new std::thread(&LoginServer::CheckLastRecvTime, this);
}