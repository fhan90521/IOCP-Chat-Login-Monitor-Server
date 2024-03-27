#pragma once
#include "ChatReqMessageJob.h"
#include "ChatServer.h"
void ChatReqMessageJob::ProcessJob()
{
	Player* pPlayer=_pServer->_playerMap[_sessionInfo.id];
	_pServer->_RecvMsgCnt++;
	List<SessionInfo> sessionInfoList;
	_pServer->GetSessionInfoAroundSector(sessionInfoList, pPlayer->_sectorX, pPlayer->_sectorY);
	_pServer->ChatResMessage(sessionInfoList, pPlayer->_accountNo, pPlayer->_id, pPlayer->_nickName, _msg);
	_pServer->_SendMsgCnt += sessionInfoList.size();
}
