#include  "CSMonitorClientProxy.h"
#include "CSMonitorPKT_TYPE.h"
void CSMonitorClientProxy::ReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char,32>& loginSessionKey, bool bDisconnect)
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
	_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::ReqLoginByMonitorTool(List<SessionInfo>& sessionInfoList, Array<char,32>& loginSessionKey, bool bDisconnect)
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
		_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::ResLoginCS(SessionInfo sessionInfo, BYTE status, bool bDisconnect)
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
	_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::ResLoginCS(List<SessionInfo>& sessionInfoList, BYTE status, bool bDisconnect)
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
		_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::MonitorToolDataUpdate(SessionInfo sessionInfo, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
	_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::MonitorToolDataUpdate(List<SessionInfo>& sessionInfoList, BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
		_pClient->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
