#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class ChatServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void ChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<char,64>& sessionKey, bool bDisconnect = false);
	void ChatReqLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<char,64>& sessionKey, bool bDisconnect = false);

	void ChatResLogin(SessionInfo sessionInfo, BYTE status, INT64 accountNo, bool bDisconnect = false);
	void ChatResLogin(const List<SessionInfo>& sessionInfoList, BYTE status, INT64 accountNo, bool bDisconnect = false);

	void ChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);
	void ChatReqSectorMove(const List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);

	void ChatResSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);
	void ChatResSectorMove(const List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);

	void ChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, const String& chatMessage, bool bDisconnect = false);
	void ChatReqMessage(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const String& chatMessage, bool bDisconnect = false);

	void ChatResMessage(SessionInfo sessionInfo, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const String& chatMessage, bool bDisconnect = false);
	void ChatResMessage(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const String& chatMessage, bool bDisconnect = false);

	void ChatReqHeartbeat(SessionInfo sessionInfo, bool bDisconnect = false);
	void ChatReqHeartbeat(const List<SessionInfo>& sessionInfoList, bool bDisconnect = false);

	ChatServerProxy(IOCPServer* pServer)
	{
		_pServer = pServer;
	}
};
