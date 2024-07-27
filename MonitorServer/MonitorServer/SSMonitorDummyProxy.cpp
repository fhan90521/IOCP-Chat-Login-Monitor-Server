#include  "SSMonitorDummyProxy.h"
#include "SSMonitorPKT_TYPE.h"
void SSMonitorDummyProxy::ReqLoginByServer(SessionInfo sessionInfo, int serverNo, bool bDisconnect)
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
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorDummyProxy::ReqLoginByServer(List<SessionInfo>& sessionInfoList, int serverNo, bool bDisconnect)
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
		_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void SSMonitorDummyProxy::MonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorDummyProxy::MonitorServerDataUpdate(List<SessionInfo>& sessionInfoList, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
		_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void SSMonitorDummyProxy::ResLoginSS(SessionInfo sessionInfo, BYTE status, bool bDisconnect)
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
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorDummyProxy::ResLoginSS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect)
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
		_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
