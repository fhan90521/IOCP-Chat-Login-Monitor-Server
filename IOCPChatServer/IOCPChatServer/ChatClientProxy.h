#pragma once
#include "Session.h"
#include "IOCPClient.h"
#include "MyStlContainer.h"
class ChatClientProxy
{
private:
	IOCPClient* _pClient;
public:
	void ChatReqLogin(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect = false);
	void ChatResLogin(BYTE status, INT64 accountNo, bool bDisconnect = false);
	void ChatReqSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);
	void ChatResSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);
	void ChatReqMessage(INT64 accountNo, Vector<char>& msg, bool bDisconnect = false);
	void ChatResMessage(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect = false);
	void ChatReqHeartbeat(bool bDisconnect = false);
	ChatClientProxy(IOCPClient* pClient)
	{
		_pClient = pClient;
	}
};
