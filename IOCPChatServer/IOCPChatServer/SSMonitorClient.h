#pragma once
#include "IOCPClient.h"
#include "SSMonitorClientProxy.h"
#include "SSMonitorClientStub.h"
class SSMonitorClient: public	IOCPClient, public SSMonitorClientProxy, public SSMonitorClientStub
{
private:
	virtual void OnConnect() {};
	virtual void OnDisconnect() override;
	virtual void OnRecv(CRecvBuffer& buf) override;
	virtual void ProcResLoginSS(BYTE status) override;
	int _monitorServerId;
public:
	//연결이 끊겨있으면 네트워크 라이브러리 내부적으로 알아서 send를 하지 않지만 쓸데없는 일을 줄이기 위한 플래그 딱히 동기화용은 아니라 atomic변수일 필요가 없음.
	//만약 끊기고 재연결에 실패하면 계속 쓸데없는 함수가 호출됨.
	bool _bLoginSuccess = false;
	SSMonitorClient();
	virtual ~SSMonitorClient();
	virtual void Run() override;
};