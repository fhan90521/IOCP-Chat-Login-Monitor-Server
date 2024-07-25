#pragma once
#include "IOCPClient.h"
#include "SSMonitorClientProxy.h"
#include "SSMonitorClientStub.h"
class SSMonitorClient: public	IOCPClient, public SSMonitorClientProxy, public SSMonitorClientStub
{
private:
	virtual void OnConnect() {};
	virtual void OnDisconnect() override;
	virtual void OnRecv(CRecvBuffer& buf) override;
	virtual void ProcResLoginSS(BYTE status) override;
public:
	bool _bLoginSuccess = false;
	SSMonitorClient();
	virtual void Run() override;
};