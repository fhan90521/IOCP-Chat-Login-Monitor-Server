#include "ChatRoom.h"
#include "ChatPlayer.h"
#include "ChatServer.h"
#include "ChatSession.h"
void ChatRoom::CheckHeartBeat()
{
    ULONG64 currentTime = GetTickCount64();
    for (auto& temp : _chatSessionMap)
    {
        ChatSession* pSession=temp.second;
        if (currentTime - pSession->lastRecvTime > 40000)
        {
            _pServer->Disconnect(pSession->sessionInfo);
        }
    }
}
void ChatRoom::HeartBeatCS(SessionInfo sessionInfo)
{
    auto iter =_chatSessionMap.find(sessionInfo.Id());
    if (iter != _chatSessionMap.end())
    {
        ChatSession* pSession = iter->second;
        pSession->lastRecvTime = GetTickCount64();
    }
    else
    {
        _pServer->Disconnect(sessionInfo);
    }
}
void ChatRoom::OnEnter(SessionInfo sessionInfo)
{
    auto iter  = _chatSessionMap.find(sessionInfo.Id());
    if (iter == _chatSessionMap.end())
    {
        ChatSession* newSession = New<ChatSession>();
        newSession->lastRecvTime = GetTickCount64();
        newSession->sessionInfo = sessionInfo;
        newSession->sessionType = SessionType::Guest;
        _chatSessionMap[sessionInfo.Id()] = newSession;
    }
    else
    {
        _pServer->Disconnect(sessionInfo);
    }
    _onConnectCnt++;
}
void ChatRoom::OnLeave (SessionInfo sessionInfo)
{
    auto iter = _chatSessionMap.find(sessionInfo.Id());
    if (iter != _chatSessionMap.end())
    {
        ChatSession* chatSession  = iter->second;
        if (chatSession->sessionType == SessionType::Player)
        {
            ChatPlayer* pPlayer = chatSession->pPlayer;
            if (pPlayer->sectorY != DEFAULT_SECTOR)
            {
                _sectorMap[pPlayer->sectorY][pPlayer->sectorX].remove(pPlayer);
            }
            _chatPlayerMap.erase(pPlayer->accountNo);
            Delete<ChatPlayer>(pPlayer);
            _playerCnt--;
       }
        _chatSessionMap.erase(iter);
        Delete<ChatSession>(chatSession);
    }
    else
    {
        _pServer->Disconnect(sessionInfo);
    }
}
void ChatRoom::Update(float deltaTime)
{
    //실제로 더미테스트에서는 heartbeat를 쏘지 않아서 
    //CheckHeartBeat();
}
void ChatRoom::GetSessionInfoAroundSector(List<SessionInfo>& sessionInfoList, WORD sectorX, WORD sectorY)
{
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            for (ChatPlayer* pPlayer : _sectorMap[sectorY + dy][sectorX + dx])
            {
                sessionInfoList.push_back(pPlayer->sessionInfo);
            }
        }
    }
}
void ChatRoom::OnLeaveRoomSystem(SessionInfo sessionInfo)
{
    OnLeave(sessionInfo);
}
ChatRoom::ChatRoom(ChatServer* pServer):Room(pServer->GetCompletionPortHandle()),_pServer(pServer)
{
}
void ChatRoom::ReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20> id, Array<WCHAR, 20> nickName)
{
    auto iter = _chatPlayerMap.find(accountNo);
    if (iter != _chatPlayerMap.end())
    {
        //서버가 아직 로그아웃 처리를 안했는데 클라이언트 다시 로그인 요청을 했을경우 여기서 끊어짐 서버가 느리면 끊어질 수 있다.
        _pServer->Disconnect(sessionInfo);
        //Log::LogOnFile(Log::SYSTEM_LEVEL, "there is aleardy accountNo in ReqLogin: %d\n", accountNo);
    }
    else
    {
        auto iterSessionMap = _chatSessionMap.find(sessionInfo.Id());
        if (iterSessionMap != _chatSessionMap.end())
        {
            ChatSession* pSession = iterSessionMap->second;
            ChatPlayer* pNewPlayer = New<ChatPlayer>();
            pNewPlayer->accountNo = accountNo;
            pNewPlayer->id = id;
            pNewPlayer->nickName = nickName;
            pNewPlayer->sectorX = DEFAULT_SECTOR;
            pNewPlayer->sectorY = DEFAULT_SECTOR;
            pNewPlayer->sessionInfo = sessionInfo;
            _chatPlayerMap[accountNo] = pNewPlayer;
            _playerCnt++;
            pSession->sessionType = SessionType::Player;
            pSession->pPlayer = pNewPlayer;
            _pServer->ChatResLogin(sessionInfo, 1, accountNo);
        }
        else
        {
            _pServer->Disconnect(sessionInfo);
        }
    }
}
void ChatRoom::ReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char> msg)
{
    auto iter = _chatPlayerMap.find(accountNo);
    if (iter != _chatPlayerMap.end())
    {
        ChatPlayer* pPlayer = iter->second;
        _ReqMsgCnt++;
        List<SessionInfo> sessionInfoList;
        GetSessionInfoAroundSector(sessionInfoList, pPlayer->sectorX, pPlayer->sectorY);
        _pServer->ChatResMessage(sessionInfoList, pPlayer->accountNo, pPlayer->id, pPlayer->nickName, msg);
        _SendMsgCnt += sessionInfoList.size();
    }
    else
    {
        _pServer->Disconnect(sessionInfo);
        Log::LogOnFile(Log::SYSTEM_LEVEL, "ReqMessage No player");
    }
}
void ChatRoom::SectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD nextX, WORD nextY)
{
    auto iter = _chatPlayerMap.find(accountNo);
    if (iter != _chatPlayerMap.end())
    {
       ChatPlayer* pPlayer = iter->second;
        nextX++;
        nextY++;
        WORD prevX = pPlayer->sectorX;
        WORD prevY = pPlayer->sectorY;
        pPlayer->sectorX = nextX;
        pPlayer->sectorY = nextY;
        List<ChatPlayer*>& prevSector = _sectorMap[prevY][prevX];
        bool bFind = false;
        if (prevX != DEFAULT_SECTOR)
        {
            auto iter = find_if(prevSector.begin(), prevSector.end(), [pPlayer](ChatPlayer* tmp) {return tmp->accountNo == pPlayer->accountNo; });
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
    else
    {
        _pServer->Disconnect(sessionInfo);
        Log::LogOnFile(Log::SYSTEM_LEVEL, "ReqMessage No player");
    }
}