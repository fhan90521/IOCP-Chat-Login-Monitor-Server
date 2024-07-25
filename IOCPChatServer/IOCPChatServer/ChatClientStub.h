#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "ChatPKT_TYPE.h"
class ChatClientStub
{
public:
	bool PacketProcChatReqLogin(CRecvBuffer& buf);
	virtual void ProcChatReqLogin(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey ){}

	bool PacketProcChatResLogin(CRecvBuffer& buf);
	virtual void ProcChatResLogin(BYTE status, INT64 accountNo ){}

	bool PacketProcChatReqSectorMove(CRecvBuffer& buf);
	virtual void ProcChatReqSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY ){}

	bool PacketProcChatResSectorMove(CRecvBuffer& buf);
	virtual void ProcChatResSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY ){}

	bool PacketProcChatReqMessage(CRecvBuffer& buf);
	virtual void ProcChatReqMessage(INT64 accountNo, Vector<char>& msg ){}

	bool PacketProcChatResMessage(CRecvBuffer& buf);
	virtual void ProcChatResMessage(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg ){}

	bool PacketProcChatReqHeartbeat(CRecvBuffer& buf);
	virtual void ProcChatReqHeartbeat( ){}

	bool PacketProc(CRecvBuffer& buf);
};
