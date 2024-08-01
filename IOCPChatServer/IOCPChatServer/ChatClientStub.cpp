#include "ChatClientStub.h"
#include "IOCPServer.h"
#include "Log.h"
using namespace std;
bool ChatClientStub::PacketProcChatReqLogin(CRecvBuffer& buf)
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
	ProcChatReqLogin(accountNo, id, nickName, sessionKey);
	return true;
}

bool ChatClientStub::PacketProcChatResLogin(CRecvBuffer& buf)
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
	ProcChatResLogin(status, accountNo);
	return true;
}

bool ChatClientStub::PacketProcChatReqSectorMove(CRecvBuffer& buf)
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
	ProcChatReqSectorMove(accountNo, sectorX, sectorY);
	return true;
}

bool ChatClientStub::PacketProcChatResSectorMove(CRecvBuffer& buf)
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
	ProcChatResSectorMove(accountNo, sectorX, sectorY);
	return true;
}

bool ChatClientStub::PacketProcChatReqMessage(CRecvBuffer& buf)
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
	ProcChatReqMessage(accountNo, msg);
	return true;
}

bool ChatClientStub::PacketProcChatResMessage(CRecvBuffer& buf)
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
	ProcChatResMessage(accountNo, id, nickName, msg);
	return true;
}

bool ChatClientStub::PacketProcChatReqHeartbeat(CRecvBuffer& buf)
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
	ProcChatReqHeartbeat();
	return true;
}

bool ChatClientStub::PacketProc(CRecvBuffer& buf)
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
	case PKT_TYPE_ChatReqLogin:
	{
		return PacketProcChatReqLogin(buf);
		break;
	}
	case PKT_TYPE_ChatResLogin:
	{
		return PacketProcChatResLogin(buf);
		break;
	}
	case PKT_TYPE_ChatReqSectorMove:
	{
		return PacketProcChatReqSectorMove(buf);
		break;
	}
	case PKT_TYPE_ChatResSectorMove:
	{
		return PacketProcChatResSectorMove(buf);
		break;
	}
	case PKT_TYPE_ChatReqMessage:
	{
		return PacketProcChatReqMessage(buf);
		break;
	}
	case PKT_TYPE_ChatResMessage:
	{
		return PacketProcChatResMessage(buf);
		break;
	}
	case PKT_TYPE_ChatReqHeartbeat:
	{
		return PacketProcChatReqHeartbeat(buf);
		break;
	}
	default:
	{
		return false;
	}
	}
}
