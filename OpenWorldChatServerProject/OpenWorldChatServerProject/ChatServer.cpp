#include "ChatServer.h"
#include "ChatRoom.h"
#include "ChatReqLoginJob.h"
#include "Remotable.h"
#include "OnDisconnectJob.h"
#include "OnConnectJob.h"
#include "SectorMoveJob.h"
#include "ChatReqMessageJob.h"
#include "HeartBeatJob.h"
#include <iostream>
#include <format>
bool ChatServer::OnAcceptRequest(const char* ip, USHORT port)
{
    return true;
}

void ChatServer::OnAccept(SessionInfo sessionInfo)
{
    OnConnectJob* pJob = New<OnConnectJob>();
    pJob->_pServer = this;
    pJob->_sessionInfo = sessionInfo;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

void ChatServer::OnDisconnect(SessionInfo sessionInfo)
{
    OnDisconnectJob* pJob = New<OnDisconnectJob>();
    pJob->_pServer = this;
    pJob->_sessionInfo = sessionInfo;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

void ChatServer::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
    if (PacketProc(sessionInfo, buf) == false)
    {
        Disconnect(sessionInfo);
    }
}

void ChatServer::ProcChatReqLogin(SessionInfo sessionInfo, INT64 accountNo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& nickName, Array<char, 64>& sessionKey)
{  
    ChatReqLoginJob* pJob = New<ChatReqLoginJob>();
    pJob->_sessionInfo = sessionInfo;
    pJob->_pServer = this;
    pJob->_accountNo = accountNo;
    pJob->_id = id;
    pJob->_nickName = nickName;
    pJob->_sessionKey = sessionKey;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

void ChatServer::ProcChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY)
{
    SectorMoveJob* pJob= New<SectorMoveJob>();
    pJob->_sessionInfo = sessionInfo;
    pJob->_pServer = this;
    pJob->_accountNo = accountNo;
    pJob->_nextX = sectorX+1;
    pJob->_nextY = sectorY+1;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

void ChatServer::ProcChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg)
{
    ChatReqMessageJob* pJob = New<ChatReqMessageJob>();
    pJob->_sessionInfo = sessionInfo;
    pJob->_accountNo = accountNo;
    pJob->_msg = msg;
    pJob->_pServer = this;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

void ChatServer::ProcChatReqHeartbeat(SessionInfo sessionInfo)
{
    HeartBeatJob* pJob = New<HeartBeatJob>();
    pJob->_pServer = this;
    pJob->_sessionInfo = sessionInfo;
    _JobQ.Enqueue(pJob);
    SetEvent(_hJobEvent);
}

unsigned ChatServer::JobWorkFunc(PVOID pVoid)
{
    ChatServer* pServer = (ChatServer*)pVoid;
    pServer->JobWork();
    return 0;
}

int ChatServer::GetReqMsgCnt()
{
    int ret = _RecvMsgCnt;
    _RecvMsgCnt = 0;
    return ret;
}


int ChatServer::GetResMsgCnt()
{
    int ret = _SendMsgCnt;
    _SendMsgCnt = 0;
    return ret;
}

void ChatServer::Monitor()
{
    std::cout << std::format(R"(
-------------------------------------
SessionNum: {}
JobQ len: {}
                                    
Allocating Player: {}
PlayerCnt: {}
 
Accept Total: {}                                   
Accept Tps: {}
Update Tps: {}
RecvMessageTps: {}
SendMessageTps: {}
ReqMsgTps: {}
ResMsgTps: {}

)",GetConnectingSessionCnt(), pRoom->GetJobQueueLen(), GetAllocatingCnt<Player>(), pRoom->GetPlayerCnt(), _onConnectCnt, GetAcceptCnt(), pRoom->GetUpdateCnt(), GetRecvCnt(), GetSendCnt(), GetReqMsgCnt(), GetResMsgCnt());
    _monitor.PrintMonitorData();
}

ChatServer::ChatServer():ChatServerProxy(this)
{
    pRoom = new ChatRoom(this);
    _monitor.AddInterface(BIND_IP);
}

ChatServer::~ChatServer()
{
    delete pRoom;
}

void ChatServer::Run()
{
    IOCPRun();
}
