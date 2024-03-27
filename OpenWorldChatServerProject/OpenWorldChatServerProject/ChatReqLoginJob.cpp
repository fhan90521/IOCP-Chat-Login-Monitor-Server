#include "ChatReqLoginJob.h"
#include "ChatServer.h"
#include "MyNew.h"
#include "Player.h"
#include <iostream>
#include "Log.h"
void ChatReqLoginJob::ProcessJob()
{
	Remotable remotable=_pServer->_guestMap[_sessionInfo.id];
	_pServer->_guestMap.erase(_sessionInfo.id);

	auto iter = _pServer->_accountNoMap.find(_accountNo);
	if (iter != _pServer->_accountNoMap.end())
	{
		Player* pPlayer=iter->second;
		_pServer->Disconnect(pPlayer->_sessionInfo);
		_pServer->Disconnect(_sessionInfo);
	}
	else
	{
		Player* pNewPlayer = New<Player>();
		pNewPlayer->_accountNo = _accountNo;
		pNewPlayer->_id = _id;
		pNewPlayer->_nickName = _nickName;
		pNewPlayer->_sectorX = DEFAULT_SECTOR;
		pNewPlayer->_sectorY = DEFAULT_SECTOR;
		pNewPlayer->_sessionInfo = _sessionInfo;
		pNewPlayer->_prevHeartBeat = GetTickCount64();
		pNewPlayer->_timeOutInterval = 40000;

		_pServer->_accountNoMap[_accountNo]= pNewPlayer;
		_pServer->_playerMap[_sessionInfo.id] = pNewPlayer;
		_pServer->ChatResLogin(_sessionInfo, 1, _accountNo);
	}
}
