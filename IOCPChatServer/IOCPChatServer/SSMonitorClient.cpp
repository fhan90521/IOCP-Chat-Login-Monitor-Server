#include "SSMonitorClient.h"
#include "MonitorProtocol.h"
#include "Log.h"
void SSMonitorClient::OnDisconnect()
{
	_bLoginSuccess = false;
	if (Connect() == true)
	{
		ReqLoginByServer(SERVER_TYPE::CHAT_SERVER_1);
	}
	else
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "ReConnect Error");
		//DebugBreak();
	}
}

void SSMonitorClient::OnRecv(CRecvBuffer& buf)
{
	if (PacketProc(buf) == false)
	{
		Log::LogOnFile(Log::SYSTEM_LEVEL, "Monitor Client Packet Proc Error");
		Disconnect();
	}
}

void SSMonitorClient::ProcResLoginSS(BYTE status)
{
	if (status == dfMONITOR_TOOL_LOGIN_OK)
	{
		_bLoginSuccess = true;
	}
	else
	{

		Log::LogOnFile(Log::SYSTEM_LEVEL,"Monitor Login Error%d\n", status);
	}
}

SSMonitorClient::SSMonitorClient(): IOCPClient("SSMonitorClientSetting.json",false ), SSMonitorClientProxy(this)
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
	else
	{
		ReqLoginByServer(SERVER_TYPE::CHAT_SERVER_1);
	}
}
