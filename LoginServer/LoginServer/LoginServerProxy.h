#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class LoginServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void ReqLogin(SessionInfo sessionInfo, INT64 accountNo, const Array<char,64>& sessionKey, bool bDisconnect = false);
	void ReqLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<char,64>& sessionKey, bool bDisconnect = false);

	void ResLogin(SessionInfo sessionInfo, INT64 accountNo, BYTE status, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, const Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect = false);
	void ResLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, BYTE status, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, const Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect = false);

	LoginServerProxy(IOCPServer* pServer)
	{
		_pServer = pServer;
	}
};
