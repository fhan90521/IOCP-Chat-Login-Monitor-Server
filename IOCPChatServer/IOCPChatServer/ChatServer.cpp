#include "ChatServer.h"
#include "ChatRoom.h"
#include "MonitorProtocol.h"
#include "ChatRoomSystem.h"
#include "MakeShared.h"
#include <iostream>
#include <format>
bool ChatServer::OnAcceptRequest(const char* ip, USHORT port)
{
    return true;
}

void ChatServer::OnAccept(SessionInfo sessionInfo)
{
    _onConnectCnt++;
    _chatRoomSystem->EnterRoomSystem(sessionInfo, _chatRoomID);
}

void ChatServer::OnDisconnect(SessionInfo sessionInfo)
{
    _chatRoomSystem->LeaveRoomSystem(sessionInfo);
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
    _loginTokenRedis.GetRedisConnection()->get(std::to_string(accountNo), [this, sessionInfo, accountNo, id, nickName, sessionKey](cpp_redis::reply& reply) mutable {
        if (reply.is_bulk_string() && memcmp(sessionKey.data(), reply.as_string().data(), 64) == 0)
        {
            _chatRoom->DoAsync(&ChatRoom::ReqLogin, sessionInfo, accountNo, id, nickName);
        }
        else
        {
            Disconnect(sessionInfo);
        }
     });
    _loginTokenRedis.GetRedisConnection()->commit();
}

void ChatServer::ProcChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY)
{
    _chatRoom->DoAsync(&ChatRoom::SectorMove, sessionInfo, accountNo, sectorX , sectorY );
}

void ChatServer::ProcChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, String& chatMessage)
{
    _chatRoom->DoAsync(&ChatRoom::ReqMessage, sessionInfo, accountNo, chatMessage);
}

void ChatServer::ProcChatReqHeartbeat(SessionInfo sessionInfo)
{
    _chatRoom->DoAsync(&ChatRoom::HeartBeatCS, sessionInfo);
}

void ChatServer::Monitor()
{
    int ProcessJobCnt = _chatRoom->GetProcessedJobCnt();
    int bufAllocCnt = CSendBuffer::GetAllocCnt();
    std::cout << std::format(R"(
-------------------------------------
SessionNum: {}
JobQ len: {}
                                    
Allocating Player: {}
PlayerCnt: {}

SendBufPool : {}
Accept Total: {}                                   
Accept Tps: {}
ProcessJob Tps:{}
RecvMessageTps: {}
SendMessageTps: {}
ReqMsgTps: {}
ResMsgTps: {}

)", GetConnectingSessionCnt(), _chatRoom->GetJobQueueLen(), GlobalObjectPool<ChatPlayer >::GetAllocatingCnt(), _chatRoom->GetPlayerCnt(), bufAllocCnt, _onConnectCnt, GetAcceptCnt(), ProcessJobCnt,GetRecvCnt(), GetSendCnt(), _chatRoom->GetReqMsgCnt(), _chatRoom->GetSendMsgCnt());
    _monitor.PrintMonitorData();
    time_t currentTime;
    time(&currentTime);
    if (_monitorClient._bLoginSuccess)
    {
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_RUN, true, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_CPU, _monitor.GetProcessCpuTotal(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_MEM, _monitor.GetProcessUserMemoryByMB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SESSION, GetConnectingSessionCnt(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_PLAYER, _chatRoom->GetPlayerCnt(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_UPDATE_TPS, ProcessJobCnt, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_PACKET_POOL, bufAllocCnt, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_UPDATEMSG_POOL, _chatRoom->GetJobQueueLen(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL, _monitor.GetSystemCpuTotal(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY, _monitor.GetSystemNonPagedByMB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV, _monitor.GetInDataSizeByKB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND, _monitor.GetOutDataSizeByKB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY, _monitor.GetSystemAvailMemoryByGB() * 1000, currentTime);
    }
}

ChatServer::ChatServer():ChatServerProxy(this),IOCPServer("ChatServerSetting.json"), _loginTokenRedis("ChatServerSetting.json")
{
    _chatRoomSystem = new ChatRoomSystem(this);
    _chatRoom = MakeShared<ChatRoom>(this);
    _chatRoomID =_chatRoomSystem->RegisterRoom(_chatRoom);
    _monitor.AddInterface(GetBindIp());
    _monitorClient.Run();
}

ChatServer::~ChatServer()
{
    _chatRoomSystem->DeregisterRoom(_chatRoomID);
    delete _chatRoomSystem;
    CloseServer();
}

void ChatServer::Run()
{
    IOCPRun();
}
