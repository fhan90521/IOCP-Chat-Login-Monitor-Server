#include "LoginServerStub.h"
#include "IOCPServer.h"
#include "Log.h"
bool LoginServerStub::PacketProcReqLogin(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	Array<char,64> sessionKey;
	try
	{
		buf >> accountNo >> sessionKey;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcReqLogin error\n");
		return false;
	}
	ProcReqLogin(sessionInfo, accountNo, sessionKey);
	return true;
}

bool LoginServerStub::PacketProcResLogin(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	BYTE status;
	Array<WCHAR,20> id;
	Array<WCHAR,20> nickName;
	Array<WCHAR,16> gameServerIp;
	USHORT gameServerPort;
	Array<WCHAR,16> chatServerIp;
	USHORT chatServerPort;
	try
	{
		buf >> accountNo >> status >> id >> nickName >> gameServerIp >> gameServerPort >> chatServerIp >> chatServerPort;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcResLogin error\n");
		return false;
	}
	ProcResLogin(sessionInfo, accountNo, status, id, nickName, gameServerIp, gameServerPort, chatServerIp, chatServerPort);
	return true;
}

bool LoginServerStub::PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf)
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
	case PKT_TYPE_ReqLogin:
	{
		return PacketProcReqLogin(sessionInfo, buf);
		break;
	}
	case PKT_TYPE_ResLogin:
	{
		return PacketProcResLogin(sessionInfo, buf);
		break;
	}
	default:
	{
		return false;
	}
	}
}
