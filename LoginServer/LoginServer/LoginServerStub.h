#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "LoginServerPKT_TYPE.h"
class LoginServerStub
{
public:
	bool PacketProcReqLogin( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcReqLogin( SessionInfo sessionInfo, INT64 accountNo, Array<char,64>& sessionKey ){}

	bool PacketProcResLogin( SessionInfo sessionInfo, CRecvBuffer& buf);
	virtual void ProcResLogin( SessionInfo sessionInfo, INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort ){}

	bool PacketProc(SessionInfo sessionInfo, CRecvBuffer& buf);
};
