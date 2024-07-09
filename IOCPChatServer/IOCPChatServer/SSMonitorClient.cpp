#include "SSMonitorClient.h"
#include "MonitorProtocol.h"

void SSMonitorClient::OnDisconnect(SessionInfo sessionInfo)
{
	_bLoginSuccess = false;
	if (Connect(_sessionInfo) == true)
	{
		ReqLoginByServer(_sessionInfo, SERVER_TYPE::CHAT_SERVER_1);
	}
	else
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "ReConnect Error");
		DebugBreak();
	}
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

SSMonitorClient::SSMonitorClient(): IOCPClient("ClientSettingFile.json",false ), SSMonitorClientProxy(this)
{
}

void SSMonitorClient::Run()
{
	IOCPRun();
	if (Connect(_sessionInfo) == false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "First Connect Error");
		DebugBreak();
	}
	else
	{
		ReqLoginByServer(_sessionInfo, SERVER_TYPE::CHAT_SERVER_1);
	}
}
