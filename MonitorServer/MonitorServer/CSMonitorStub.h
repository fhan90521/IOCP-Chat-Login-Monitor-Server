#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "CSMonitorPKT_TYPE.h"
class CSMonitorStub
{
public:
	bool PacketProcReqLoginByMonitorTool( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcReqLoginByMonitorTool( SessionInfo sessionInfo, Array<char,32>& loginSessionKey ){}

	bool PacketProcResLoginCS( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcResLoginCS( SessionInfo sessionInfo, BYTE status ){}

	bool PacketProcMonitorToolDataUpdate( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcMonitorToolDataUpdate( SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp ){}

	bool PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf);
};
