#include  "CSMonitorClientProxy.h"
#include "CSMonitorPKT_TYPE.h"
void CSMonitorClientProxy::ReqLoginByMonitorTool(Array<char,32>& loginSessionKey, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::ResLoginCS(BYTE status, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void CSMonitorClientProxy::MonitorToolDataUpdate(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
