#include "ChatRoom.h"
#include "Player.h"
#include "ChatServer.h"
void ChatRoom::OnEnter(SessionInfo sessionInfo)
{
    Remotable guestUser(sessionInfo, GetTickCount64(), 40000);
    _guestMap[sessionInfo.id] = guestUser;
    _onConnectCnt++;
}

int ChatRoom::RequestEnter(SessionInfo sessionInfo)
{
    return ENTER_SUCCESS;
}

void ChatRoom::OnLeave(SessionInfo sessionInfo)
{
    Player* pPlayer;
    auto iter = _playerMap.find(sessionInfo.id);
    if (iter != _playerMap.end())
    {
        pPlayer = iter->second;
        if (pPlayer->_sectorY != DEFAULT_SECTOR)
        {
            _sectorMap[pPlayer->_sectorY][pPlayer->_sectorX].remove(pPlayer);
        }
        _playerMap.erase(iter);
        _playerCnt--;
        _accountNoMap.erase(pPlayer->_accountNo);
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
                sessionInfoList.push_back(pPlayer->_sessionInfo);
            }
        }
    }
}

ChatRoom::ChatRoom(ChatServer* pServer):Room(pServer),_pServer(pServer)
{
}

void ChatRoom::ReqLogin(SessionInfo _sessionInfo, INT64 _accountNo, Array<WCHAR, 20> _id, Array<WCHAR, 20> _nickName)
{
    Remotable remotable = _guestMap[_sessionInfo.id];
    _guestMap.erase(_sessionInfo.id);

    auto iter = _accountNoMap.find(_accountNo);
    if (iter != _accountNoMap.end())
    {
        Player* pPlayer = iter->second;
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

        _accountNoMap[_accountNo] = pNewPlayer;
        _playerMap[_sessionInfo.id] = pNewPlayer;
        _playerCnt++;
        _pServer->ChatResLogin(_sessionInfo, 1, _accountNo);
    }
}

void ChatRoom::ReqMessage(SessionInfo _sessionInfo, INT64 _accountNo, Vector<char> _msg)
{
    Player* pPlayer = _playerMap[_sessionInfo.id];
    _ReqMsgCnt++;
    List<SessionInfo> sessionInfoList;
    GetSessionInfoAroundSector(sessionInfoList, pPlayer->_sectorX, pPlayer->_sectorY);
    _pServer->ChatResMessage(sessionInfoList, pPlayer->_accountNo, pPlayer->_id, pPlayer->_nickName, _msg);
    _SendMsgCnt += sessionInfoList.size();
}

void ChatRoom::SectorMove(SessionInfo _sessionInfo, INT64 _accountNo, WORD _nextX, WORD _nextY)
{
    _nextX++;
    _nextY++;
    Player* pPlayer = _playerMap[_sessionInfo.id];
    WORD prevX = pPlayer->_sectorX;
    WORD prevY = pPlayer->_sectorY;
    pPlayer->_sectorX = _nextX;
    pPlayer->_sectorY = _nextY;
    List<Player*>& prevSector = _sectorMap[prevY][prevX];
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
    _sectorMap[_nextY][_nextX].push_back(pPlayer);
    _pServer->ChatResSectorMove(pPlayer->_sessionInfo, _accountNo, _nextX, _nextY);
}

void ChatRoom::HeartBeat(SessionInfo _sessionInfo)
{
    Player* pPlayer = _playerMap[_sessionInfo.id];
    pPlayer->_prevHeartBeat = GetTickCount64();
    _pServer->ChatReqHeartbeat(_sessionInfo);
}
