#pragma once
#include "LoginServerProxy.h"
#include "LoginServerStub.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
#include "SSMonitorClient.h"
#include "PerformanceMonitor.h"
#include <atomic>
#include "WorkThreadPool.h"
#include <thread>
class LoginServer: public IOCPServer, public  LoginServerProxy, public LoginServerStub
{
private:
	Array<WCHAR, 16>_chatServerIp;
	USHORT _chatServerPort;
	Array<WCHAR, 16> _gameServerIp;
	USHORT _gameServerPort;
	LONG64 _onConnectCnt = 0;
	LONG _procLoginReqCnt = 0;
	LONG GetProcLoginReqCnt();
public:
	const Array<WCHAR, 16>& GetChatServerIp();
	USHORT GetChatServerPort();
	const Array<WCHAR, 16>& GetGameServerIp();
	USHORT GetGameServerPort();
	void IncrementLoginReqCnt();
private:
	enum
	{
		RECV_TIME_OUT = 30000
	};
	std::thread* _checkRecvTimeThread;
	typedef ULONG64 LastRecvTime;
	HashMap<SessionInfo::ID, LastRecvTime> _sessionMap;
	USE_LOCK;
	HANDLE _hShutDownEvent;
	void CheckLastRecvTime();

	WorkThreadPool* _dbWorkThreadPool;
	Vector<SharedPtr<class LoginDBJobQueue>> _dbJobQueues;
	int _dbQueueIndex = 0;
	int _dbConcurrentWorkThreadCnt = 2;
	virtual bool OnAcceptRequest(const char* ip, USHORT port) override;
	virtual void OnAccept(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;
	virtual void ProcReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char, 64>& sessionKey) override;

	PerformanceMonitor _monitor;
	SSMonitorClient _monitorClient;
public:
	virtual void Run() override;
	void Monitor();
	LoginServer();
	~LoginServer();

};