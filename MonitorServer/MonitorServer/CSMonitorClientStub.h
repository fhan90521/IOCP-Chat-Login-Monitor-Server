#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "CSMonitorPKT_TYPE.h"
class CSMonitorClientStub
{
public:
	bool PacketProcReqLoginByMonitorTool(CRecvBuffer& buf);
	virtual void ProcReqLoginByMonitorTool(Array<char,32>& loginSessionKey ){}

	bool PacketProcResLoginCS(CRecvBuffer& buf);
	virtual void ProcResLoginCS(BYTE status ){}

	bool PacketProcMonitorToolDataUpdate(CRecvBuffer& buf);
	virtual void ProcMonitorToolDataUpdate(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp ){}

	bool PacketProc(CRecvBuffer& buf);
};
