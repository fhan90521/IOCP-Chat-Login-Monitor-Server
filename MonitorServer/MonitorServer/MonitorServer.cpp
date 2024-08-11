#include "MonitorServer.h"
#include "MonitorProtocol.h"
#include <format>
#include "CSMonitorServer.h"
bool MonitorServer::OnAcceptRequest(const char* ip, USHORT port)
{
    return true;
}

MonitorServer::~MonitorServer()
{
    for (auto& tmp : _monitorDatasMap)
    {
        MonitorDatas* pMonitorDatas = tmp.second;
        delete pMonitorDatas;
    }
    delete _pCSMonitorServer;
}

void MonitorServer::OnAccept(SessionInfo sessionInfo)
{
    return;
}

void MonitorServer::OnDisconnect(SessionInfo sessionInfo)
{
    AcquireSRWLockExclusive(&_serverNoLock);
    auto iter = _serverNoMap.find(sessionInfo.Id());
    if (iter != _serverNoMap.end())
    {
        int serverNo = iter->second;
        _severNoSet.erase(serverNo);
        _serverNoMap.erase(iter);
        delete _monitorDatasMap[serverNo];
    }
    ReleaseSRWLockExclusive(&_serverNoLock);
}

void MonitorServer::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
    if (PacketProc(sessionInfo, buf) == false)
    {
        Disconnect(sessionInfo);
    }
 
}

void MonitorServer::ProcReqLoginByServer(SessionInfo sessionInfo, int serverNo)
{
    AcquireSRWLockExclusive(&_serverNoLock);
    auto retInsert=_severNoSet.insert(serverNo);
    if (retInsert.second == true)
    {
        _serverNoMap[sessionInfo.Id()] = serverNo;
        _monitorDatasMap[serverNo] = new MonitorDatas();
        ResLoginSS(sessionInfo, dfMONITOR_TOOL_LOGIN_OK);
    }
    else
    {
        ResLoginSS(sessionInfo, dfMONITOR_TOOL_LOGIN_ERR_NOSERVER,true);
    }
    ReleaseSRWLockExclusive(&_serverNoLock);
}

void MonitorServer::ProcMonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp)
{
    int serverNo;
    AcquireSRWLockShared(&_serverNoLock);
    serverNo = _serverNoMap[sessionInfo.Id()];
    ReleaseSRWLockShared(&_serverNoLock);

    _pCSMonitorServer->BroadcastUpdate(serverNo, dataType, dataValue, timeStamp);
    
    MonitorDatas* pMonitorDatas=_monitorDatasMap[serverNo];
    if (pMonitorDatas == nullptr)
    {
        Disconnect(sessionInfo);
        return;
    }

    if (pMonitorDatas->_cnt[dataType] == 0)
    {
        pMonitorDatas->_min[dataType] = INT_MAX;
    }

    // Recv 1회제한 특정 서버에서 오는 패킷 recv처리는 하나의 스레드가 담당-> 락을 잡을 필요가 없다  
    pMonitorDatas->_cnt[dataType]++;
    pMonitorDatas->_avg[dataType] += dataValue;     
    pMonitorDatas->_max[dataType] = max(pMonitorDatas->_max[dataType], dataValue);
    pMonitorDatas->_min[dataType] = min(pMonitorDatas->_min[dataType], dataValue);
    if (pMonitorDatas->_cnt[dataType] >= 60)
    {
        pMonitorDatas->_avg[dataType] = pMonitorDatas->_avg[dataType] / pMonitorDatas->_cnt[dataType];
        LogOnDB(serverNo, dataType, pMonitorDatas->_avg[dataType], pMonitorDatas->_min[dataType], pMonitorDatas->_max[dataType]);
        pMonitorDatas->_cnt[dataType] = 0;
        pMonitorDatas->_avg[dataType] = 0;
        pMonitorDatas->_max[dataType] = 0;
        //pMonitorDatas->_min[dataType] = INT_MAX;
    }
  
}

MonitorServer::MonitorServer():IOCPServer("SSMonitorServerSetting.json",false), SSMonitorServerProxy(this),_logDB("SSMonitorServerSetting.json")
{
    InitializeSRWLock(&_serverNoLock);
    _pCSMonitorServer = new CSMonitorServer;
    _pCSMonitorServer->Run();
}

void MonitorServer::Run()
{
    IOCPRun();
}

void MonitorServer::Monitor()
{
    std::cout << std::format(R"(
-------------------------------------                               
ConnectingServerCnt : {}
ConnectingClientCnt:{}
AcceptCnt : {}
RecvMessageTps: {}
SendMessageTps: {}
)", GetConnectingSessionCnt(),_pCSMonitorServer->GetConnectingSessionCnt(), GetAcceptCnt(), GetRecvCnt(), GetSendCnt());
    _pCSMonitorServer->CheckSessionStatus();
}

void MonitorServer::LogOnDB(int serverNo, int type, float avr, int min, int max)
{
    MYSQL* connection = _logDB.GetConnection();
    char query[512];
    MYSQLHelper::MakeQuery(query, 512, "INSERT INTO `logdb`.`monitorlog` (`serverNo`, `type`, `avr`, `min`, `max`) VALUES('%d', '%d', '%f', '%d','%d')", serverNo, type, avr, min, max);
    int queryStat = mysql_query(connection, query);
    if (queryStat != 0)
    {
        Log::LogOnFile(Log::SYSTEM_LEVEL, "Mysql query error : %s", mysql_error(connection));
        _logDB.CloseConnection();
    }
}
