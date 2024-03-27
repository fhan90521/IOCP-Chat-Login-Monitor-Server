#include "HeartBeatJob.h"
#include "ChatServer.h"
void HeartBeatJob::ProcessJob()
{
	Player* pPlayer=_pServer->_playerMap[_sessionInfo.id];
	pPlayer->_prevHeartBeat = GetTickCount64();
	_pServer->ChatReqHeartbeat(_sessionInfo);
}
