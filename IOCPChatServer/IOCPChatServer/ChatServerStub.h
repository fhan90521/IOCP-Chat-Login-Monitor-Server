#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "ChatServerPKT_TYPE.h"
class ChatServerStub
{
public:
	bool PacketProcChatReqLogin( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatReqLogin( SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey ){}

	bool PacketProcChatResLogin( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatResLogin( SessionInfo sessionInfo, BYTE status, INT64 accountNo ){}

	bool PacketProcChatReqSectorMove( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatReqSectorMove( SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY ){}

	bool PacketProcChatResSectorMove( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatResSectorMove( SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY ){}

	bool PacketProcChatReqMessage( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatReqMessage( SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg ){}

	bool PacketProcChatResMessage( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatResMessage( SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg ){}

	bool PacketProcChatReqHeartbeat( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcChatReqHeartbeat( SessionInfo sessionInfo ){}

	bool PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf);
};
