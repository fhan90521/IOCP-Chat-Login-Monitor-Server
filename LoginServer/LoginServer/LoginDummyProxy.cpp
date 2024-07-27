#include  "LoginDummyProxy.h"
#include "LoginPKT_TYPE.h"
void LoginDummyProxy::ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<char,64>& sessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLogin << accountNo << sessionKey;
	}
	catch(int useSize)
	{
	}
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void LoginDummyProxy::ReqLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, Array<char,64>& sessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLogin << accountNo << sessionKey;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void LoginDummyProxy::ResLogin(SessionInfo sessionInfo, INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLogin << accountNo << status << id << nickName << gameServerIp << gameServerPort << chatServerIp << chatServerPort;
	}
	catch(int useSize)
	{
	}
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void LoginDummyProxy::ResLogin(List<SessionInfo>& sessionInfoList, INT64 accountNo, BYTE status, Array<WCHAR,20>& id, Array<WCHAR,20>& nickName, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLogin << accountNo << status << id << nickName << gameServerIp << gameServerPort << chatServerIp << chatServerPort;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
