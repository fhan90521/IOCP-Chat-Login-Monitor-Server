#pragma once
#include "LoginServerProxy.h"
#include "LoginServerStub.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
#include "SSMonitorClient.h"
#include "PerformanceMonitor.h"
#include <atomic>
#include "WorkThreadPool.h"
class LoginServer: public IOCPServer, public  LoginServerProxy, public LoginServerStub
{
public:
	Array<WCHAR, 16>_chatServerIpArr;
	USHORT _chatServerPort;
	Array<WCHAR, 16> _gameServerIpArr;
	USHORT _gameServerPort;
	LONG64 _onConnectCnt=0;
	LONG _procLoginReqCnt = 0;
private:
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
	LONG GetProcLoginReqCnt()
	{
		int ret = _procLoginReqCnt;
		InterlockedExchange(&_procLoginReqCnt, 0);
		return ret;
	}
	virtual void Run() override;
	void Monitor();
	LoginServer();
	~LoginServer();

};