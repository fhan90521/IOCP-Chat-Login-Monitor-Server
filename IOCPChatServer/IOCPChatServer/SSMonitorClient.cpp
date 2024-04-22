#include "SSMonitorClient.h"
#include "MonitorProtocol.h"
void SSMonitorClient::OnConnect(SessionInfo sessionInfo)
{
	_sessionInfo = sessionInfo;
	ReqLoginByServer(_sessionInfo, SERVER_TYPE::CHAT_SERVER_1);
	return;
}

void SSMonitorClient::OnConnectFail(int error)
{
	Connect();
	return;
}

void SSMonitorClient::OnDisconnect(SessionInfo sessionInfo)
{
	_bLoginSuccess = false;
	Connect();
}

void SSMonitorClient::OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf)
{
	if (PacketProc(sessionInfo,buf) == false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "Monitor Client Packet Proc Error");
		Disconnect(sessionInfo);
	}
}

void SSMonitorClient::ProcResLoginSS(SessionInfo sessionInfo, BYTE status)
{
	if (status == dfMONITOR_TOOL_LOGIN_OK)
	{
		_bLoginSuccess = true;
	}
}

SSMonitorClient::SSMonitorClient(): IOCPClient(false), SSMonitorClientProxy(this)
{
}

void SSMonitorClient::Run()
{
	IOCPRun();
	if (Connect() == false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "First Connect Error");
		DebugBreak();
	}
}
