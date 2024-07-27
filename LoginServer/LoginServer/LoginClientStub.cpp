#include  "LoginClientStub.h"
 #include <iostream>
#include "Log.h"
using namespace std;
bool LoginClientStub::PacketProcReqLogin(CRecvBuffer& buf)
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
	ProcReqLogin(accountNo, sessionKey);
	return true;
}
bool LoginClientStub::PacketProcResLogin(CRecvBuffer& buf)
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
	ProcResLogin(accountNo, status, id, nickName, gameServerIp, gameServerPort, chatServerIp, chatServerPort);
	return true;
}

bool LoginClientStub::PacketProc(CRecvBuffer& buf)
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
	case PKT_TYPE_ReqLogin:
	{
		return PacketProcReqLogin(buf);
		break;
	}
	case PKT_TYPE_ResLogin:
	{
		return PacketProcResLogin(buf);
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
