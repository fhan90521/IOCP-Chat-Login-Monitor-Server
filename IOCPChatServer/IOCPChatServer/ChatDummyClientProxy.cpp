#include "ChatDummyClientProxy.h"
#include "ChatPKT_TYPE.h"
void ChatDummyClientProxy::ChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect)
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
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect)
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
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResLogin(SessionInfo sessionInfo, BYTE status, INT64 accountNo, bool bDisconnect)
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
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResLogin(List<SessionInfo>& sessionInfoList, BYTE status, INT64 accountNo, bool bDisconnect)
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
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResSectorMove(List<SessionInfo>& sessionInfoList, INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqMessage << accountNo << msg;
	}
	catch(int useSize)
	{
	}
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Vector<char>& msg, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatReqMessage << accountNo << msg;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResMessage(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResMessage << accountNo << id << nickName << msg;
	}
	catch(int useSize)
	{
	}
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatResMessage(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ChatResMessage << accountNo << id << nickName << msg;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqHeartbeat(SessionInfo sessionInfo, bool bDisconnect)
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
	_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatDummyClientProxy::ChatReqHeartbeat(List<SessionInfo>& sessionInfoList, bool bDisconnect)
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
		_pDummyClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
