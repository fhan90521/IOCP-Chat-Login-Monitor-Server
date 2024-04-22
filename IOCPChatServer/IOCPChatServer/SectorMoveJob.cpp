#include "SectorMoveJob.h"
#include "ChatServer.h"
#include "Session.h"
#include "Log.h"
void SectorMoveJob::ProcessJob()
{
    Player* pPlayer = _pServer->_playerMap[_sessionInfo.id];
    WORD prevX = pPlayer->_sectorX;
    WORD prevY = pPlayer->_sectorY;
    pPlayer->_sectorX = _nextX;
    pPlayer->_sectorY = _nextY;
    List<Player*>& prevSector = _pServer->_sectorMap[prevY][prevX];
    bool bFind = false;
    if (prevX != DEFAULT_SECTOR)
    {
        auto iter = find_if(prevSector.begin(), prevSector.end(), [pPlayer](Player* tmp) {return tmp->_accountNo == pPlayer->_accountNo; });
        if (iter == prevSector.end())
        {
            Log::LogOnFile(Log::SYSTEM_LEVEL, "there is no Player in Sector accountNo: %d", pPlayer->_accountNo);
        }
        else
        {
            prevSector.erase(iter);
        }
    }
     _pServer->_sectorMap[_nextY][_nextX].push_back(pPlayer);
     _pServer->ChatResSectorMove(pPlayer->_sessionInfo, _accountNo, _nextX, _nextY); 
}
