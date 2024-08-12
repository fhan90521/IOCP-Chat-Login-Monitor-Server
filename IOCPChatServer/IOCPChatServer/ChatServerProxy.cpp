#include "ChatServerProxy.h"
#include "ChatPKT_TYPE.h"
void ChatServerProxy::ChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<char,64>& sessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqLogin << accountNo << id << nickName << sessionKey;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<char,64>& sessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqLogin << accountNo << id << nickName << sessionKey;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResLogin(SessionInfo sessionInfo, BYTE status, INT64 accountNo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResLogin << status << accountNo;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResLogin(const List<SessionInfo>& sessionInfoList, BYTE status, INT64 accountNo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResLogin << status << accountNo;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqSectorMove << accountNo << sectorX << sectorY;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqSectorMove(const List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqSectorMove << accountNo << sectorX << sectorY;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResSectorMove << accountNo << sectorX << sectorY;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResSectorMove(const List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResSectorMove << accountNo << sectorX << sectorY;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, const String& chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqMessage << accountNo << chatMessage;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqMessage(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const String& chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqMessage << accountNo << chatMessage;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResMessage(SessionInfo sessionInfo, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const String& chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResMessage << accountNo << id << nickName << chatMessage;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatResMessage(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const String& chatMessage, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResMessage << accountNo << id << nickName << chatMessage;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqHeartbeat(SessionInfo sessionInfo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqHeartbeat;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatServerProxy::ChatReqHeartbeat(const List<SessionInfo>& sessionInfoList, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqHeartbeat;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
