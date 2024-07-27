#include  "CSMonitorClientStub.h"
 #include <iostream>
#include "Log.h"
using namespace std;
bool CSMonitorClientStub::PacketProcReqLoginByMonitorTool(CRecvBuffer& buf)
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
	ProcReqLoginByMonitorTool(loginSessionKey);
	return true;
}
bool CSMonitorClientStub::PacketProcResLoginCS(CRecvBuffer& buf)
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
	ProcResLoginCS(status);
	return true;
}
bool CSMonitorClientStub::PacketProcMonitorToolDataUpdate(CRecvBuffer& buf)
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
	ProcMonitorToolDataUpdate(serverNo, dataType, dataValue, timeStamp);
	return true;
}

bool CSMonitorClientStub::PacketProc(CRecvBuffer& buf)
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
		return PacketProcReqLoginByMonitorTool(buf);
		break;
	}
	case PKT_TYPE_ResLoginCS:
	{
		return PacketProcResLoginCS(buf);
		break;
	}
	case PKT_TYPE_MonitorToolDataUpdate:
	{
		return PacketProcMonitorToolDataUpdate(buf);
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
