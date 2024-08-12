#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MyStlContainer.h"
#include "SSMonitorPKT_TYPE.h"
class SSMonitorClientStub
{
public:
	bool PacketProcReqLoginByServer(CRecvBuffer& buf);
	virtual void ProcReqLoginByServer(int serverNo) {}

	bool PacketProcMonitorServerDataUpdate(CRecvBuffer& buf);
	virtual void ProcMonitorServerDataUpdate(BYTE dataType, int dataValue, int timeStamp) {}

	bool PacketProcResLoginSS(CRecvBuffer& buf);
	virtual void ProcResLoginSS(BYTE status) {}

	bool PacketProc(CRecvBuffer& buf);
};
