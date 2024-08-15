#pragma once
#include "IOCPServer.h"
#include "CSMonitorServerProxy.h"
#include "CSMonitorServerStub.h"
class CSMonitorServer: public IOCPServer, public CSMonitorServerProxy, private CSMonitorServerStub
{
private:
	struct SessionStatus
	{
		enum
		{
			BEFORE_LOGIN,
			AFTER_LOGIN,
			BEFORE_LOGIN_TIMEOUT = 3,
			AFTER_LOGIN_TIMEOUT = 30
		};
		int status = BEFORE_LOGIN;
		__time32_t lastRecvTime;
		SessionStatus()
		{
			lastRecvTime = _time32(&lastRecvTime);
		}
	};
	HashMap<SessionInfo::ID, SessionStatus> _sessionStatusMap;
	SRWLOCK _sessionStatusLock;
	List<SessionInfo> _monitorToolSessionInfoList;
	SRWLOCK _monitorToolListLock;
	Array<char, 33> _logInSessionKey;
	virtual bool OnAcceptRequest(const char* ip, USHORT port) override;
	virtual void OnAccept(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;
	virtual void ProcReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char, 32>& loginSessionKey) override;
public:
	virtual void Run() override;
	CSMonitorServer();
	void CheckSessionStatus();
	void BroadcastUpdate(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp);
};