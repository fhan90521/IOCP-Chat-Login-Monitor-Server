#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class CSMonitorServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void ReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char,32>& loginSessionKey, bool bDisconnect = false );
	void ReqLoginByMonitorTool(List<SessionInfo>& sessionInfoList, Array<char,32>& loginSessionKey, bool bDisconnect = false);

	void ResLoginCS(SessionInfo sessionInfo, BYTE status, bool bDisconnect = false );
	void ResLoginCS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect = false);

	void MonitorToolDataUpdate(SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	void MonitorToolDataUpdate(List<SessionInfo>& sessionInfoList, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	CSMonitorServerProxy(IOCPServer* pServer)
	{
		_pServer=pServer;
	}
};
