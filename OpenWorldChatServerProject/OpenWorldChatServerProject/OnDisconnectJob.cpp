#include "OnDisconnectJob.h"
#include "ChatServer.h"
#include "Log.h"
void OnDisconnectJob::ProcessJob()
{
    Player* pPlayer;
    auto iter =  _pServer->_playerMap.find(_sessionInfo.id);
    if (iter != _pServer->_playerMap.end())
    {
        pPlayer =iter->second;
        if (pPlayer->_sectorY != DEFAULT_SECTOR)
        {
            _pServer->_sectorMap[pPlayer->_sectorY][pPlayer->_sectorX].remove(pPlayer);
        }
        _pServer->_playerMap.erase(iter);
        _pServer->_accountNoMap.erase(pPlayer->_accountNo);
        Delete<Player>(pPlayer);
    }
    else
    {
        if (_pServer->_guestMap.erase(_sessionInfo.id) == 0)
        {
            Log::LogOnFile(Log::SYSTEM_LEVEL, "there is no guest session ID: %d", _sessionInfo.id);
        }
    }
}
