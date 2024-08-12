#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class SSMonitorClientProxy
{
private:
	IOCPClient* _pClient;
public:
	void ReqLoginByServer(int serverNo, bool bDisconnect = false);
	void MonitorServerDataUpdate(BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);
	void ResLoginSS(BYTE status, bool bDisconnect = false);
	SSMonitorClientProxy(IOCPClient* pClient)
	{
		_pClient = pClient;
	}
};
