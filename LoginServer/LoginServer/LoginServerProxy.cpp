#include "LoginServerProxy.h"
#include "LoginPKT_TYPE.h"
void LoginServerProxy::ReqLogin(SessionInfo sessionInfo, INT64 accountNo, const Array<char,64>& sessionKey, bool bDisconnect)
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
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void LoginServerProxy::ReqLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, const Array<char,64>& sessionKey, bool bDisconnect)
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
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void LoginServerProxy::ResLogin(SessionInfo sessionInfo, INT64 accountNo, BYTE status, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, const Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect)
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
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void LoginServerProxy::ResLogin(const List<SessionInfo>& sessionInfoList, INT64 accountNo, BYTE status, const Array<WCHAR,20>& id, const Array<WCHAR,20>& nickName, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, const Array<WCHAR,16>& chatServerIp, USHORT chatServerPort, bool bDisconnect)
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
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
