#include "ChatServer.h"
#include "ChatRoom.h"
#include "Remotable.h"
#include "MonitorProtocol.h"
#include <iostream>
#include <format>
#include <MakeShared.h>
bool ChatServer::OnAcceptRequest(const char* ip, USHORT port)
{
    return true;
}

void ChatServer::OnAccept(SessionInfo sessionInfo)
{
    _onConnectCnt++;
    _pRoom->EnterRoom(sessionInfo);
}

void ChatServer::OnDisconnect(SessionInfo sessionInfo)
{
    _pRoom->LeaveRoom(sessionInfo);
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
    bool bSuccess = false;
    _redisManager.GetRedisConnection()->get(std::to_string(accountNo), [&sessionKey, &bSuccess](cpp_redis::reply& reply) {
        if (reply.is_bulk_string() && memcmp(sessionKey.data(), reply.as_string().data(), 64) == 0)
        {
            bSuccess = true;
        }
     });
    _redisManager.GetRedisConnection()->sync_commit();
    if (bSuccess)
    {
        _pRoom->TryDoSync(&ChatRoom::ReqLogin, sessionInfo, accountNo, id, nickName);
    }
    else
    {
        Disconnect(sessionInfo);
    }
}

void ChatServer::ProcChatReqSectorMove(SessionInfo sessionInfo, INT64 accountNo, WORD sectorX, WORD sectorY)
{
    _pRoom->TryDoSync(&ChatRoom::SectorMove, sessionInfo, accountNo, sectorX , sectorY );
}

void ChatServer::ProcChatReqMessage(SessionInfo sessionInfo, INT64 accountNo, Vector<char>& msg)
{
    _pRoom->TryDoSync(&ChatRoom::ReqMessage, sessionInfo, accountNo, msg);
}

void ChatServer::ProcChatReqHeartbeat(SessionInfo sessionInfo)
{
    _pRoom->TryDoSync(&ChatRoom::HeartBeat, sessionInfo);
}


void ChatServer::Monitor()
{
    int ProcessJobCnt = _pRoom->GetProcessedJobCnt();
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

)", GetConnectingSessionCnt(), _pRoom->GetJobQueueLen(), GetAllocatingCnt<Player>(), _pRoom->GetPlayerCnt(), bufAllocCnt, _onConnectCnt, GetAcceptCnt(), ProcessJobCnt,GetRecvCnt(), GetSendCnt(), _pRoom->GetReqMsgCnt(), _pRoom->GetSendMsgCnt());
    _monitor.PrintMonitorData();
    time_t currentTime;
    time(&currentTime);
    if (_monitorClient._bLoginSuccess)
    {
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_RUN, true, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_CPU, _monitor.GetProcessCpuTotal(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SERVER_MEM, _monitor.GetProcessUserMemoryByMB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_SESSION, GetConnectingSessionCnt(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_PLAYER, _pRoom->GetPlayerCnt(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_UPDATE_TPS, ProcessJobCnt, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_PACKET_POOL, bufAllocCnt, currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_CHAT_UPDATEMSG_POOL, _pRoom->GetJobQueueLen(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL, _monitor.GetSystemCpuTotal(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY, _monitor.GetSystemNonPagedByMB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV, _monitor.GetInDataSizeByKB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND, _monitor.GetOutDataSizeByKB(), currentTime);
        _monitorClient.MonitorServerDataUpdate(dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY, _monitor.GetSystemAvailMemoryByGB() * 1000, currentTime);
    }
}

ChatServer::ChatServer():ChatServerProxy(this),IOCPServer("ChatServerSetting.json"),_redisManager("ChatServerSetting.json")
{
    _pRoom = MakeShared<ChatRoom>(this);
    _monitor.AddInterface(BIND_IP);
    _monitorClient.Run();
}

ChatServer::~ChatServer()
{
}

void ChatServer::Run()
{
    IOCPRun();
}
