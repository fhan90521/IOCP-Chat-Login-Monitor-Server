#pragma once
#include "Session.h"
#include "IOCPServer.h"
#include "MyStlContainer.h"
class ChatServerProxy
{
private:
	IOCPServer* _pServer;
public:
	void ChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey );
	void ChatReqLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey );

	void ChatResLogin(SessionInfo sessionInfo, BYTE status, INT64 accountNo );
	void ChatResLogin(List<SessionInfo>& sessionInfoList, BYTE status, INT64 accountNo );

	void ChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY );
	void ChatReqSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY );

	void ChatResSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY );
	void ChatResSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY );

	void ChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg );
	void ChatReqMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Vector<char>& msg );

	void ChatResMessage(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg );
	void ChatResMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg );

	void ChatReqHeartbeat(SessionInfo sessionInfo );
	void ChatReqHeartbeat(List<SessionInfo>& sessionInfoList );

	ChatServerProxy(IOCPServer* pServer)
	{
		_pServer=pServer;
	}
};
