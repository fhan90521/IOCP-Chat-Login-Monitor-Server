#include  "SSMonitorClientProxy.h"
#include "SSMonitorPKT_TYPE.h"
void SSMonitorClientProxy::ReqLoginByServer(int serverNo, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorClientProxy::MonitorServerDataUpdate(BYTE dataType, int dataValue, int timeStamp, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void SSMonitorClientProxy::ResLoginSS(BYTE status, bool bDisconnect)
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
	_pClient->Unicast(pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
