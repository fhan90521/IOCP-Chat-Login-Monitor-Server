#include  "SSMonitorClientStub.h"
 #include <iostream>
#include "Log.h"
using namespace std;
bool SSMonitorClientStub::PacketProcReqLoginByServer(CRecvBuffer& buf)
{
	int serverNo;
	try
	{
		buf >> serverNo;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcReqLoginByServer error\n");
		 return false;
	}
	ProcReqLoginByServer(serverNo);
	return true;
}
bool SSMonitorClientStub::PacketProcMonitorServerDataUpdate(CRecvBuffer& buf)
{
	BYTE dataType;
	int dataValue;
	int timeStamp;
	try
	{
		buf >> dataType >> dataValue >> timeStamp;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcMonitorServerDataUpdate error\n");
		 return false;
	}
	ProcMonitorServerDataUpdate(dataType, dataValue, timeStamp);
	return true;
}
bool SSMonitorClientStub::PacketProcResLoginSS(CRecvBuffer& buf)
{
	BYTE status;
	try
	{
		buf >> status;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcResLoginSS error\n");
		 return false;
	}
	ProcResLoginSS(status);
	return true;
}

bool SSMonitorClientStub::PacketProc(CRecvBuffer& buf)
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
	case PKT_TYPE_ReqLoginByServer:
	{
		return PacketProcReqLoginByServer(buf);
		break;
	}
	case PKT_TYPE_MonitorServerDataUpdate:
	{
		return PacketProcMonitorServerDataUpdate(buf);
		break;
	}
	case PKT_TYPE_ResLoginSS:
	{
		return PacketProcResLoginSS(buf);
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
