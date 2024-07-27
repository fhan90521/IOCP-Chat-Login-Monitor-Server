#include  "CSMonitorDummyProxy.h"
#include "CSMonitorPKT_TYPE.h"
void CSMonitorDummyProxy::ReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char,32>& loginSessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLoginByMonitorTool << loginSessionKey;
	}
	catch(int useSize)
	{
	}
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorDummyProxy::ReqLoginByMonitorTool(List<SessionInfo>& sessionInfoList, Array<char,32>& loginSessionKey, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLoginByMonitorTool << loginSessionKey;
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
void CSMonitorDummyProxy::ResLoginCS(SessionInfo sessionInfo, BYTE status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLoginCS << status;
	}
	catch(int useSize)
	{
	}
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorDummyProxy::ResLoginCS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLoginCS << status;
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
void CSMonitorDummyProxy::MonitorToolDataUpdate(SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_MonitorToolDataUpdate << serverNo << dataType << dataValue << timeStamp;
	}
	catch(int useSize)
	{
	}
	_pDummy->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorDummyProxy::MonitorToolDataUpdate(List<SessionInfo>& sessionInfoList, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_MonitorToolDataUpdate << serverNo << dataType << dataValue << timeStamp;
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
