#include  "ChatServerStub.h"
 #include "IOCPServer.h"
#include <iostream>
#include "Log.h"
using namespace std;
bool ChatServerStub::PacketProcChatReqLogin(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	Array<WCHAR,20> id;
	Array<WCHAR,20> nickName;
	Array<char,64> sessionKey;
	try
	{
		buf >> accountNo >> id >> nickName >> sessionKey;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatReqLogin error\n");
		 return false;
	}
	ProcChatReqLogin( sessionInfo , accountNo, id, nickName, sessionKey);
	return true;
}
bool ChatServerStub::PacketProcChatResLogin(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	BYTE status;
	INT64 accountNo;
	try
	{
		buf >> status >> accountNo;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatResLogin error\n");
		 return false;
	}
	ProcChatResLogin( sessionInfo , status, accountNo);
	return true;
}
bool ChatServerStub::PacketProcChatReqSectorMove(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	WORD sectorX;
	WORD sectorY;
	try
	{
		buf >> accountNo >> sectorX >> sectorY;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatReqSectorMove error\n");
		 return false;
	}
	ProcChatReqSectorMove( sessionInfo , accountNo, sectorX, sectorY);
	return true;
}
bool ChatServerStub::PacketProcChatResSectorMove(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	WORD sectorX;
	WORD sectorY;
	try
	{
		buf >> accountNo >> sectorX >> sectorY;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatResSectorMove error\n");
		 return false;
	}
	ProcChatResSectorMove( sessionInfo , accountNo, sectorX, sectorY);
	return true;
}
bool ChatServerStub::PacketProcChatReqMessage(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	Vector<char> msg;
	try
	{
		buf >> accountNo >> msg;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatReqMessage error\n");
		 return false;
	}
	ProcChatReqMessage( sessionInfo , accountNo, msg);
	return true;
}
bool ChatServerStub::PacketProcChatResMessage(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	INT64 accountNo;
	Array<WCHAR,20> id;
	Array<WCHAR,20> nickName;
	Vector<char> msg;
	try
	{
		buf >> accountNo >> id >> nickName >> msg;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatResMessage error\n");
		 return false;
	}
	ProcChatResMessage( sessionInfo , accountNo, id, nickName, msg);
	return true;
}
bool ChatServerStub::PacketProcChatReqHeartbeat(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	try
	{
		buf;
	}
	catch(int useSize)
	{
		 Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcChatReqHeartbeat error\n");
		 return false;
	}
	ProcChatReqHeartbeat( sessionInfo );
	return true;
}

bool ChatServerStub::PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf)
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
	case PKT_TYPE_ChatReqLogin:
	{
		return PacketProcChatReqLogin(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatResLogin:
	{
		return PacketProcChatResLogin(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatReqSectorMove:
	{
		return PacketProcChatReqSectorMove(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatResSectorMove:
	{
		return PacketProcChatResSectorMove(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatReqMessage:
	{
		return PacketProcChatReqMessage(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatResMessage:
	{
		return PacketProcChatResMessage(sessionInfo,buf);
		break;
	}
	case PKT_TYPE_ChatReqHeartbeat:
	{
		return PacketProcChatReqHeartbeat(sessionInfo,buf);
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
