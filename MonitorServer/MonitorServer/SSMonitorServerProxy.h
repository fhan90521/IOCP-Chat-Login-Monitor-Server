#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class SSMonitorServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void ReqLoginByServer(SessionInfo sessionInfo, int serverNo, bool bDisconnect = false);
	void ReqLoginByServer(const List<SessionInfo>& sessionInfoList, int serverNo, bool bDisconnect = false);

	void MonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);
	void MonitorServerDataUpdate(const List<SessionInfo>& sessionInfoList, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	void ResLoginSS(SessionInfo sessionInfo, BYTE status, bool bDisconnect = false);
	void ResLoginSS(const List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect = false);

	SSMonitorServerProxy(IOCPServer* pServer)
	{
		_pServer = pServer;
	}
};
