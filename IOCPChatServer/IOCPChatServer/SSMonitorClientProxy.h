#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class SSMonitorClientProxy
{
private:
IOCPClient* _pClient;
public:
	void ReqLoginByServer(SessionInfo sessionInfo, int serverNo, bool bDisconnect = false );
	void ReqLoginByServer(List<SessionInfo>& sessionInfoList, int serverNo, bool bDisconnect = false);

	void MonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	void MonitorServerDataUpdate(List<SessionInfo>& sessionInfoList, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	void ResLoginSS(SessionInfo sessionInfo, BYTE status, bool bDisconnect = false );
	void ResLoginSS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect = false);

	SSMonitorClientProxy(IOCPClient* pClient)
	{
		_pClient=pClient;
	}
};
