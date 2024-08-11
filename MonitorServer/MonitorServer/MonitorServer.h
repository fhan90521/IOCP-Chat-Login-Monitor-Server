#pragma once
#include "IOCPServer.h"
#include "MyStlContainer.h"
#include "SSMonitorServerProxy.h"
#include "SSMonitorServerStub.h"
#include "MYSQLHelper.h"
#include <time.h>
class MonitorServer :public IOCPServer, public SSMonitorServerProxy, public SSMonitorServerStub
{
private:
	MYSQLHelper _logDB;
	class CSMonitorServer* _pCSMonitorServer = nullptr;
	HashMap<SessionInfo::ID,int> _serverNoMap;
	HashSet<int> _severNoSet;
	SRWLOCK _lock;
	SharedPtr<class DBJobQueue>_pDBJobQ;
	struct MonitorDatas
	{
		HashMap<int, int> _cnt;
		HashMap<int, int>_avg;
		HashMap<int, int>_max;
		HashMap<int, int> _min;
	};
	HashMap<int, MonitorDatas*> _monitorDatasMap;
	virtual bool OnAcceptRequest(const char* ip, USHORT port) override;
	virtual void OnAccept(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo, CRecvBuffer& buf) override;

	virtual void ProcReqLoginByServer(SessionInfo sessionInfo, int serverNo) override;
	virtual void ProcMonitorServerDataUpdate(SessionInfo sessionInfo, BYTE dataType, int dataValue, int timeStamp) override;

	void LogOnDB(int serverNo, int type, float avr, int min, int max);
public:
	MonitorServer();
	~MonitorServer();
	virtual void Run() override;
	void CheckSessionStatus();
	void Monitor();
};