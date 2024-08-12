#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MyStlContainer.h"
#include "SSMonitorPKT_TYPE.h"
class SSMonitorServerStub
{
public:
	bool PacketProcReqLoginByServer(SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcReqLoginByServer(SessionInfo sessionInfo, int serverNo) {}

	bool PacketProcMonitorServerDataUpdate(SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcMonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp) {}

	bool PacketProcResLoginSS(SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcResLoginSS(SessionInfo sessionInfo, BYTE status) {}

	bool PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf);
};
