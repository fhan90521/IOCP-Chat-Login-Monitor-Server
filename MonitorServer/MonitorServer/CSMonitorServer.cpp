#include "CSMonitorServer.h"
#include "MonitorProtocol.h"
bool CSMonitorServer::OnAcceptRequest(const char* ip, USHORT port)
{
	return true;
}

void CSMonitorServer::OnAccept(SessionInfo sessionInfo)
{
	AcquireSRWLockExclusive(&_sessionStatusLock);
	_sessionStatusMap[sessionInfo.Id()];
	ReleaseSRWLockExclusive(&_sessionStatusLock);

}

void CSMonitorServer::OnDisconnect(SessionInfo sessionInfo)
{
	AcquireSRWLockExclusive(&_sessionStatusLock);
	_sessionStatusMap.erase(sessionInfo.Id());
	ReleaseSRWLockExclusive(&_sessionStatusLock);

    AcquireSRWLockExclusive(&_monitorToolListLock);
    _monitorToolSessionInfoList.remove(sessionInfo);
    ReleaseSRWLockExclusive(&_monitorToolListLock);
}

void CSMonitorServer::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
    if (PacketProc(sessionInfo, buf) == false)
    {
        Disconnect(sessionInfo);
    }
    else
    {
        AcquireSRWLockExclusive(&_sessionStatusLock);
        _time32(&_sessionStatusMap[sessionInfo.Id()].lastRecvTime);
        ReleaseSRWLockExclusive(&_sessionStatusLock);
    }
}

void CSMonitorServer::ProcReqLoginByMonitorTool(SessionInfo sessionInfo, Array<char, 32>& loginSessionKey)
{
    if (memcmp(_logInSessionKey.data(), loginSessionKey.data(), 32) != 0)
    {
        ResLoginCS(sessionInfo, dfMONITOR_TOOL_LOGIN_ERR_SESSIONKEY, true);
        return;
    }
    AcquireSRWLockExclusive(&_monitorToolListLock);
    _monitorToolSessionInfoList.push_back(sessionInfo);
    ReleaseSRWLockExclusive(&_monitorToolListLock);
    _sessionStatusMap[sessionInfo.Id()].status = SessionStatus::AFTER_LOGIN;
    ResLoginCS(sessionInfo, dfMONITOR_TOOL_LOGIN_OK);
}

void CSMonitorServer::Run()
{
    IOCPRun();
}

CSMonitorServer::CSMonitorServer():IOCPServer("CSMonitorServerSetting.json",true),CSMonitorServerProxy(this)
{
	InitializeSRWLock(&_sessionStatusLock);
    InitializeSRWLock(&_monitorToolListLock);
    strcpy_s(_logInSessionKey.data(), 33, "ajfw@!cv980dSZ[fje#@fdj123948djf");
}

void CSMonitorServer::CheckSessionStatus()
{
  
    __time32_t currentTime;
    _time32(&currentTime);
    AcquireSRWLockExclusive(&_sessionStatusLock);
    for (auto tmp : _sessionStatusMap)
    {
        SessionInfo sessionInfo = tmp.first;
        SessionStatus sessionStatus = tmp.second;

        if (sessionStatus.status == SessionStatus::BEFORE_LOGIN)
        {
            if (currentTime - sessionStatus.lastRecvTime > SessionStatus::BEFORE_LOGIN_TIMEOUT)
            {
                Disconnect(sessionInfo);
            }
        }
    }
    ReleaseSRWLockExclusive(&_sessionStatusLock);
}

void CSMonitorServer::BroadcastUpdate(BYTE serverNo, BYTE dataType, int dataValue, int timeStamp)
{
    AcquireSRWLockShared(&_monitorToolListLock);
    MonitorToolDataUpdate(_monitorToolSessionInfoList, serverNo, dataType, dataValue, timeStamp);
    ReleaseSRWLockShared(&_monitorToolListLock);
}
