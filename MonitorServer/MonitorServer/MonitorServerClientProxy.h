#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class MonitorServerClientProxy
{
private:
IOCPClient* _pClient;
public:
	void ReqLoginByServer(SessionInfo sessionInfo, int serverNo, bool bDisconnect = false );
	void ReqLoginByServer(List<SessionInfo>& sessionInfoList, int serverNo, bool bDisconnect = false);

	void MonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	void MonitorServerDataUpdate(List<SessionInfo>& sessionInfoList, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	void ReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char,32>& loginSessionKey, bool bDisconnect = false );
	void ReqLoginByMonitorTool(List<SessionInfo>& sessionInfoList, Array<char,32>& loginSessionKey, bool bDisconnect = false);

	void ResLogin(SessionInfo sessionInfo, BYTE status, bool bDisconnect = false );
	void ResLogin(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect = false);

	void MonitorToolDataUpdate(SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	void MonitorToolDataUpdate(List<SessionInfo>& sessionInfoList, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	MonitorServerClientProxy(IOCPClient* pClient)
	{
		_pClient=pClient;
	}
};
