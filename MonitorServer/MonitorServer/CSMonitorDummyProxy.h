#pragma once
#include "Session.h"
#include "IOCPDummyClient.h"
#include "MyStlContainer.h"
class CSMonitorDummyProxy
{
private:
	IOCPDummyClient* _pDummy;
public:
	void ReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char,32>& loginSessionKey, bool bDisconnect = false );
	void ReqLoginByMonitorTool(List<SessionInfo>& sessionInfoList, Array<char,32>& loginSessionKey, bool bDisconnect = false);

	void ResLoginCS(SessionInfo sessionInfo, BYTE status, bool bDisconnect = false );
	void ResLoginCS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect = false);

	void MonitorToolDataUpdate(SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false );
	void MonitorToolDataUpdate(List<SessionInfo>& sessionInfoList, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect = false);

	CSMonitorDummyProxy(IOCPDummyClient* pDummy)
	{
		_pDummy=pDummy;
	}
};
