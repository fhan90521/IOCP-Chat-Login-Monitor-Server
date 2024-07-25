#include  "ChatClientProxy.h"
#include "ChatPKT_TYPE.h"
void ChatClientProxy::ChatReqLogin(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<char,64>& sessionKey, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatResLogin(BYTE status, INT64 accountNo, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatReqSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatResSectorMove(INT64 accountNo, WORD sectorX, WORD sectorY, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatReqMessage(INT64 accountNo, Vector<char>& msg, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatResMessage(INT64 accountNo, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Vector<char>& msg, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void ChatClientProxy::ChatReqHeartbeat(bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
