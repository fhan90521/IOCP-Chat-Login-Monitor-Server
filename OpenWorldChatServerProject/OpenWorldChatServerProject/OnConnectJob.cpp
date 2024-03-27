#include "OnConnectJob.h"
#include "Remotable.h"
#include "ChatServer.h"
void OnConnectJob::ProcessJob()
{
	Remotable guestUser(_sessionInfo, GetTickCount64(), 40000);
	_pServer->_guestMap[_sessionInfo.id] = guestUser;
	_pServer->_onConnectCnt++;
}
