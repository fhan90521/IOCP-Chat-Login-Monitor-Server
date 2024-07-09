#pragma once
#include "IOCPClient.h"
#include "SSMonitorClientProxy.h"
#include "SSMonitorStub.h"
class SSMonitorClient: public	IOCPClient, public SSMonitorClientProxy, public SSMonitorStub
{
private:
	virtual void OnConnect(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;
	virtual void ProcResLoginSS(SessionInfo sessionInfo, BYTE status) override;
public:
	bool _bLoginSuccess = false;
	SessionInfo _sessionInfo;
	SSMonitorClient();
	virtual void Run() override;
};