#include "ChatRoom.h"
#include "Player.h"
#include "ChatServer.h"
void ChatRoom::OnEnter(SessionInfo sessionInfo)
{
    Remotable guestUser(sessionInfo, GetTickCount64(), 40000);
    _guestMap[sessionInfo.id] = guestUser;
    _onConnectCnt++;
}

void ChatRoom::OnLeave(SessionInfo sessionInfo)
{
    Player* pPlayer;
    auto iter = _playerMap.find(sessionInfo.id);
    if (iter != _playerMap.end())
    {
        pPlayer = iter->second;
        if (pPlayer->sectorY != DEFAULT_SECTOR)
        {
            _sectorMap[pPlayer->sectorY][pPlayer->sectorX].remove(pPlayer);
        }
        _playerMap.erase(iter);
        _playerCnt--;
        _accountNoMap.erase(pPlayer->accountNo);
        Delete<Player>(pPlayer);
    }
    else
    {
        if (_guestMap.erase(sessionInfo.id) == 0)
        {
            Log::LogOnFile(Log::SYSTEM_LEVEL, "there is no guest session ID: %d", sessionInfo.id);
        }
    }
}

void ChatRoom::GetSessionInfoAroundSector(List<SessionInfo>& sessionInfoList, WORD sectorX, WORD sectorY)
{
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            for (Player* pPlayer : _sectorMap[sectorY + dy][sectorX + dx])
            {
                sessionInfoList.push_back(pPlayer->sessionInfo);
            }
        }
    }
}

ChatRoom::ChatRoom(ChatServer* pServer):JobQueue(pServer),_pServer(pServer)
{
}

void ChatRoom::EnterRoom(SessionInfo sessionInfo)
{
    OnEnter(sessionInfo);
}

void ChatRoom::LeaveRoom(SessionInfo sessionInfo)
{
    OnLeave(sessionInfo);
}

void ChatRoom::ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20> id, Array<WCHAR, 20> nickName)
{
    Remotable remotable = _guestMap[sessionInfo.id];
    _guestMap.erase(sessionInfo.id);

    auto iter = _accountNoMap.find(accountNo);
    if (iter != _accountNoMap.end())
    {
        Player* pPlayer = iter->second;
        _pServer->Disconnect(pPlayer->sessionInfo);
        _pServer->Disconnect(sessionInfo);
    }
    else
    {
        Player* pNewPlayer = New<Player>();
        pNewPlayer->accountNo = accountNo;
        pNewPlayer->id = id;
        pNewPlayer->nickName = nickName;
        pNewPlayer->sectorX = DEFAULT_SECTOR;
        pNewPlayer->sectorY = DEFAULT_SECTOR;
        pNewPlayer->sessionInfo = sessionInfo;
        pNewPlayer->prevHeartBeat = GetTickCount64();
        pNewPlayer->timeOutInterval = 40000;

        _accountNoMap[accountNo] = pNewPlayer;
        _playerMap[sessionInfo.id] = pNewPlayer;
        _playerCnt++;
        _pServer->ChatResLogin(sessionInfo, 1, accountNo);
    }
}

void ChatRoom::ReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char> msg)
{
    Player* pPlayer = _playerMap[sessionInfo.id];
    _ReqMsgCnt++;
    List<SessionInfo> sessionInfoList;
    GetSessionInfoAroundSector(sessionInfoList, pPlayer->sectorX, pPlayer->sectorY);
    _pServer->ChatResMessage(sessionInfoList, pPlayer->accountNo, pPlayer->id, pPlayer->nickName, msg);
    _SendMsgCnt += sessionInfoList.size();
}

void ChatRoom::SectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD nextX, WORD nextY)
{
    nextX++;
    nextY++;
    Player* pPlayer = _playerMap[sessionInfo.id];
    WORD prevX = pPlayer->sectorX;
    WORD prevY = pPlayer->sectorY;
    pPlayer->sectorX = nextX;
    pPlayer->sectorY = nextY;
    List<Player*>& prevSector = _sectorMap[prevY][prevX];
    bool bFind = false;
    if (prevX != DEFAULT_SECTOR)
    {
        auto iter = find_if(prevSector.begin(), prevSector.end(), [pPlayer](Player* tmp) {return tmp->accountNo == pPlayer->accountNo; });
        if (iter == prevSector.end())
        {
            Log::LogOnFile(Log::SYSTEM_LEVEL, "there is no Player in Sector accountNo: %d", pPlayer->accountNo);
        }
        else
        {
            prevSector.erase(iter);
        }
    }
    _sectorMap[nextY][nextX].push_back(pPlayer);
    _pServer->ChatResSectorMove(pPlayer->sessionInfo, accountNo, nextX, nextY);
}

void ChatRoom::HeartBeat(SessionInfo sessionInfo)
{
    Player* pPlayer = _playerMap[sessionInfo.id];
    pPlayer->prevHeartBeat = GetTickCount64();
    _pServer->ChatReqHeartbeat(sessionInfo);
}
