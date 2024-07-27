#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class LoginClientProxy
{
private:
IOCPClient* _pClient;
public:
	void ReqLogin(INT64 accountNo, Array<char,64>& sessionKey, bool bDisconnect = false );
	void ResLogin(INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect = false );
	LoginClientProxy(IOCPClient* pClient)
	{
		_pClient=pClient;
	}
};
