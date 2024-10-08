#include "SSMonitorServerStub.h"
#include "IOCPServer.h"
#include "Log.h"
bool SSMonitorServerStub::PacketProcReqLoginByServer(SessionInfo sessionInfo, CRecvBuffer& buf)
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
	ProcReqLoginByServer(sessionInfo, serverNo);
	return true;
}

bool SSMonitorServerStub::PacketProcMonitorServerDataUpdate(SessionInfo sessionInfo, CRecvBuffer& buf)
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
	ProcMonitorServerDataUpdate(sessionInfo, dataType, dataValue, timeStamp);
	return true;
}

bool SSMonitorServerStub::PacketProcResLoginSS(SessionInfo sessionInfo, CRecvBuffer& buf)
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
	ProcResLoginSS(sessionInfo, status);
	return true;
}

bool SSMonitorServerStub::PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	short packetType;
	try
	{
		buf >> packetType;
	}
	catch(int remainSize)
	{
		return false;
	}
	switch(packetType)
	{
	case PKT_TYPE_ReqLoginByServer:
	{
		return PacketProcReqLoginByServer(sessionInfo, buf);
		break;
	}
	case PKT_TYPE_MonitorServerDataUpdate:
	{
		return PacketProcMonitorServerDataUpdate(sessionInfo, buf);
		break;
	}
	case PKT_TYPE_ResLoginSS:
	{
		return PacketProcResLoginSS(sessionInfo, buf);
		break;
	}
	default:
	{
		return false;
	}
	}
}
