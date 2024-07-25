#pragma once
#include "Session.h"
#include "IOCPDummyClient.h"
#include "MyStlContainer.h"
class ChatDummyProxy
{
private:
	IOCPDummyClient* _pDummy;
public:
	void ChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect = false );
	void ChatReqLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect = false);

	void ChatResLogin(SessionInfo sessionInfo, BYTE status, INT64 accountNo, bool bDisconnect = false );
	void ChatResLogin(List<SessionInfo>& sessionInfoList, BYTE status, INT64 accountNo, bool bDisconnect = false);

	void ChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false );
	void ChatReqSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);

	void ChatResSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false );
	void ChatResSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect = false);

	void ChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg, bool bDisconnect = false );
	void ChatReqMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Vector<char>& msg, bool bDisconnect = false);

	void ChatResMessage(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect = false );
	void ChatResMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect = false);

	void ChatReqHeartbeat(SessionInfo sessionInfo, bool bDisconnect = false );
	void ChatReqHeartbeat(List<SessionInfo>& sessionInfoList, bool bDisconnect = false);

	ChatDummyProxy(IOCPDummyClient* pDummy)
	{
		_pDummy=pDummy;
	}
};
