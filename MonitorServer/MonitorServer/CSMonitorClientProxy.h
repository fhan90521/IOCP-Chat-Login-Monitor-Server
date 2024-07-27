#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class CSMonitorClientProxy
{
private:
IOCPClient* _pClient;
public:
	void ReqLoginByMonitorTool(Array<char,32>& loginSessionKey, bool bDisconnect = false );
	void ResLoginCS(BYTE status, bool bDisconnect = false );
	void MonitorToolDataUpdate(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	CSMonitorClientProxy(IOCPClient* pClient)
	{
		_pClient=pClient;
	}
};
