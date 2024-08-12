#include "SSMonitorServerProxy.h"
#include "SSMonitorPKT_TYPE.h"
void SSMonitorServerProxy::ReqLoginByServer(SessionInfo sessionInfo, int serverNo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLoginByServer << serverNo;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorServerProxy::ReqLoginByServer(const List<SessionInfo>& sessionInfoList, int serverNo, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLoginByServer << serverNo;
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
void SSMonitorServerProxy::MonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_MonitorServerDataUpdate << dataType << dataValue << timeStamp;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorServerProxy::MonitorServerDataUpdate(const List<SessionInfo>& sessionInfoList, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_MonitorServerDataUpdate << dataType << dataValue << timeStamp;
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
void SSMonitorServerProxy::ResLoginSS(SessionInfo sessionInfo, BYTE status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLoginSS << status;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorServerProxy::ResLoginSS(const List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLoginSS << status;
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
