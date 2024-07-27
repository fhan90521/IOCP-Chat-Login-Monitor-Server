#pragma once
#include "Session.h"
#include "IOCPDummyClient.h"
#include "MyStlContainer.h"
class LoginDummyProxy
{
private:
	IOCPDummyClient* _pDummy;
public:
	void ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char,64>& sessionKey, bool bDisconnect = false );
	void ReqLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<char,64>& sessionKey, bool bDisconnect = false);

	void ResLogin(SessionInfo sessionInfo, INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect = false );
	void ResLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect = false);

	LoginDummyProxy(IOCPDummyClient* pDummy)
	{
		_pDummy=pDummy;
	}
};
