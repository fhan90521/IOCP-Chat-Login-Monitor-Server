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
	//������ ���������� ��Ʈ��ũ ���̺귯�� ���������� �˾Ƽ� send�� ���� ������ �������� ���� ���̱� ���� �÷��� ���� ����ȭ���� �ƴ϶� atomic������ �ʿ䰡 ����.
	//���� ����� �翬�ῡ �����ϸ� ��� �������� �Լ��� ȣ���.
	bool _bLoginSuccess = false;
	SSMonitorClient();
	virtual ~SSMonitorClient();
	virtual void Run() override;
};