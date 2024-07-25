#include  "CSMonitorStub.h"
 #include "IOCPServer.h"
#include <iostream>
#include "Log.h"
using namespace std;
bool CSMonitorStub::PacketProcReqLoginByMonitorTool(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	Array<char,32> loginSessionKey;
	try
	{
		buf >> loginSessionKey;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcReqLoginByMonitorTool error\n");
		 return false;
	}
	ProcReqLoginByMonitorTool( sessionInfo , loginSessionKey);
	return true;
}
bool CSMonitorStub::PacketProcResLoginCS(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	BYTE status;
	try
	{
		buf >> status;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcResLoginCS error\n");
		 return false;
	}
	ProcResLoginCS( sessionInfo , status);
	return true;
}
bool CSMonitorStub::PacketProcMonitorToolDataUpdate(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	BYTE serverNo;
	BYTE dataType;
	int dataValue;
	int timeStamp;
	try
	{
		buf >> serverNo >> dataType >> dataValue >> timeStamp;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcMonitorToolDataUpdate error\n");
		 return false;
	}
	ProcMonitorToolDataUpdate( sessionInfo , serverNo, dataType, dataValue, timeStamp);
	return true;
}

bool CSMonitorStub::PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	short packetType;
	try
	{
		buf>>packetType;
	}
	catch(int remainSize)
	{
		 return false;
	}
	switch(packetType)
	{
	case PKT_TYPE_ReqLoginByMonitorTool:
	{
		return PacketProcReqLoginByMonitorTool(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ResLoginCS:
	{
		return PacketProcResLoginCS(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_MonitorToolDataUpdate:
	{
		return PacketProcMonitorToolDataUpdate(sessionInfo,buf);
		break;
	}
	default:
	{
		Log::LogOnFile(Log::DEBUG_LEVEL,"Packet Type not exist error\n");
		return false;
		break;
	}
	}
}
