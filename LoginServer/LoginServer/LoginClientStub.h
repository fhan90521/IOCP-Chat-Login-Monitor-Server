#pragma once
#include "Session.h"
#include "CRecvBuffer.h"
#include "MakeUnique.h"
#include "MyStlContainer.h"
#include "LoginPKT_TYPE.h"
class LoginClientStub
{
public:
	bool PacketProcReqLogin(CRecvBuffer& buf);
	virtual void ProcReqLogin(INT64 accountNo, Array<char,64>& sessionKey ){}

	bool PacketProcResLogin(CRecvBuffer& buf);
	virtual void ProcResLogin(INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort ){}

	bool PacketProc(CRecvBuffer& buf);
};
